
#include <Wire.h>
#include "motor.hpp"
#include "imu.hpp"
#include <math.h>

#define DEBUG

// Motor devices and state variables
dev::Motor r_motor(34, 35, 36);
dev::Motor l_motor(39, 38, 37);

// Controller timestamp variable
unsigned long timestamp;

/** Signals the device encountered an error. **/
void error() {
  pinMode(13, OUTPUT);
    while(1) {
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
    }
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
  // Initiate motors and sensors
  r_motor.init();
  l_motor.init();
  if (!init_imu()) error();
  // Initial timestamp value
  timestamp = millis();
}

/** Calculates the new theta following the complimentary filter. **/
float comp_filter(float ang, float gyr_x, float dt, float axl_y, float axl_z) {
  static const float c = 0.98f;
  // Complimentary filter determination
  float axl_ang = 90.0f + atan2f(axl_y, axl_z) * 180.0f / PI;
  return (ang + gyr_x * dt) * c + axl_ang * (1.0f - c);
}

// Controller state variables
float i_theta = 0.0f;
float p_theta = 180.0f;
float d_theta = 0.0f;

#ifdef DEBUG
unsigned long debug = 0;
#endif

void loop() {
  static const float eq_theta = 179.3f;
  static const float K_I = 0.0f;
  static const float K_P = 65.0f;
  static const float K_D = 0.0f;
  static const unsigned long loop_delay = 3;
  // Read IMU sensors, calculate dt, and timestamp the reading
  read_imu();
  float dt = ((float)(millis() - timestamp)) / 1000.0f;
  timestamp = millis();
  // Update controller state variables
  i_theta += (p_theta - eq_theta) * dt;
  float theta = comp_filter(p_theta, imu_g.x, dt, imu_a.y, imu_a.z);
  d_theta = (theta - p_theta) / dt;
  p_theta = theta;
  // Check if robot fell over
  if (abs(p_theta - eq_theta) > 80.0f) {
    r_motor.set_speed(0);
    l_motor.set_speed(0);
    error();
  }
  // Determine controller output
  float ctrl = K_I * i_theta + K_P * (p_theta - eq_theta) + K_D * d_theta;
  r_motor.set_speed((int) ctrl);
  l_motor.set_speed((int) ctrl);
  delay(loop_delay);
#ifdef DEBUG
  if(debug++ % 15 == 0) {
    Serial.print(String(i_theta) + "," + String(p_theta) + "," + String(d_theta));
    Serial.println("," + String(ctrl));
  }
#endif
}
