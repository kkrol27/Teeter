
#include <Wire.h>
#include "motor.hpp"
#include "imu.hpp"
#include <math.h>

dev::Motor r_motor(34, 35, 36);
dev::Motor l_motor(39, 38, 37);
int speed = 0;
int oldspeed = 0;
long timestamp = 0;

struct AngVelAcc {float ang; float vel; float acc;};
struct AngVelAcc angVelAcc = {180.0f, 0.0f, 0.0f};

float prevVel = 0;

float const COMP_C = 0.8f;

static float const SCALE = 2.0f;
static float const KI = SCALE * 15.0f;
static float const KP = SCALE * 0.0f;
static float const KD = SCALE * 0.026f;
static float const setPoint = 178.0f;
static long const DELAY = 50;

inline float i_func(float ang) {
  return ang;
  //return (ang < 0.0f ? -ang * ang : ang * ang);
}

void setup() {
  r_motor.init();
  l_motor.init();
  if (!init_imu()) {
    pinMode(13, OUTPUT);
    while(1) {
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
    }
  }
  read_imu();
  timestamp = millis();
  angVelAcc.vel = imu_g.x;  
}

void CompFilter(float accelData[3], float gyroVel, float dt) {
  
  float accelAngle;
 
  // Integrate gyroscope data
  angVelAcc.ang += gyroVel*dt;
  if (abs(angVelAcc.ang - 180.0f) >= 80.0f) { // robot fell over
    r_motor.set_speed(0);
    l_motor.set_speed(0);
    pinMode(13, OUTPUT);
    while(1) {
      digitalWrite(13, HIGH);
      delay(2000);
      digitalWrite(13, LOW);
      delay(2000);
    }
  }
  else {
    // Compensate for drift with accelerometer data
    // Turning around the X axis results in a vector on the Z-axis
    accelAngle = 90.0f + atan2f(accelData[1], accelData[2])*180.0f/PI;
    angVelAcc.ang = angVelAcc.ang * COMP_C + accelAngle * (1 - COMP_C);
    angVelAcc.vel = gyroVel;
    angVelAcc.acc = (gyroVel - prevVel) / dt;
  }

  prevVel = gyroVel;
} 

float torqueMotor(float accelData[3], float gyroVel, float dt) {
  // take in the current theta and velocity values and, based on those, 
  // tell the motor how much torque (speed) to apply to wheels to stabilize
  // the robot

  float s;

  CompFilter(accelData, gyroVel, dt);

  s = KI*i_func(angVelAcc.ang - setPoint) + KP*angVelAcc.vel + KD*angVelAcc.acc;

  return s;
}

void loop() {
  float dt; int newspeed;
  read_imu();
  dt = ((float)(millis() - timestamp)) / 1000.0f;
  timestamp = millis();
  oldspeed = speed;
  newspeed = (int) torqueMotor(imu_a.a, imu_g.x, dt);
  if (newspeed > 0) {
    if (oldspeed < 0 && newspeed >= 60) {
      r_motor.set_speed(170);
      l_motor.set_speed(170);
      delay(1);
    }
    speed = (newspeed >= 60 ? newspeed : 0);
  }
  else {
    if (oldspeed > 0 && newspeed <= -60) {
      r_motor.set_speed(-170);
      l_motor.set_speed(-170);
      delay(1);
    }
    speed = (newspeed <= -60 ? newspeed : 0);
  }
  r_motor.set_speed(speed);
  l_motor.set_speed(speed);
  
  delay(DELAY);
}
