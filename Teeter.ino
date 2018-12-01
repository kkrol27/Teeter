
// #include "motor.hpp"
#include "LSM6.h"

#define DEBUG

/*
dev::Motor r_motor(0, 1, 2);
dev::Motor l_motor(11, 12, 10);
int speed = -255;
int ds;
*/

LSM6 imu;

void setup() {

#ifdef DEBUG
  Serial.begin(9600);
#endif
/*
  r_motor.init();
  l_motor.init();
*/
  if (!imu.init()){
    Serial.println("imu.init fail");
    while(1){
      ;
    }
  }
  imu.enableDefault();
}

void loop() {
  imu.read();
  delay(1000);
#ifdef DEBUG
  Serial.println("acc = " + String(imu.a.x) + "," + String(imu.a.y) + "," + String(imu.a.z));
  Serial.println("gyr = " + String(imu.g.x) + "," + String(imu.g.y) + "," + String(imu.g.z));
#endif
/*
  delay(500);
  r_motor.set_speed(speed);
  l_motor.set_speed(speed);
  if (speed >= 255) ds = -5;
  if (speed <= -255) ds = 5;
  speed = speed + ds;
*/

}
