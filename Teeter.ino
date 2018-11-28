
#include "motor.hpp"

#define DEBUG

dev::Motor r_motor(0, 1, 2);
dev::Motor l_motor(11, 12, 10);
int speed = -255;
int ds;

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
  r_motor.init();
  l_motor.init();
}

void loop() {
  delay(500);
  r_motor.set_speed(speed);
  l_motor.set_speed(speed);
  if (speed >= 255) ds = -5;
  if (speed <= -255) ds = 5;
  speed = speed + ds;
}
