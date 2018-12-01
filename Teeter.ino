
#include <Wire.h>
#include "motor.hpp"
#include "LSM6.h"
#include "LIS3MDL.h"

// #define DEBUG

dev::Motor r_motor(34, 35, 36);
dev::Motor l_motor(39, 38, 37);
int speed = -255;
int ds;

LSM6 imu;
LIS3MDL mag;

void setup() {
  Wire.begin();
#ifdef DEBUG
  Serial.begin(9600);
#endif
  r_motor.init();
  l_motor.init();
  bool f = imu.init();
  if(!mag.init() || !f) {
#ifdef DEBUG
    Serial.println("init fail");
#endif
    pinMode(13, OUTPUT);
    while(1) {
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
    }
  }
  imu.enableDefault();
  mag.enableDefault();
}

void loop() {
  imu.read();
  mag.read();
  delay(1000);
#ifdef DEBUG
  Serial.println("acc = " + String(imu.a.x) + "," + String(imu.a.y) + "," + String(imu.a.z));
  Serial.println("gyr = " + String(imu.g.x) + "," + String(imu.g.y) + "," + String(imu.g.z));
  Serial.println("mag = " + String(mag.m.x) + "," + String(mag.m.y) + "," + String(mag.m.z));
#endif
  r_motor.set_speed(speed);
  l_motor.set_speed(speed);
  if (speed >= 255) ds = -5;
  if (speed <= -255) ds = 5;
  speed = speed + ds;
}
