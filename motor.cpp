//
// AEP 3630 Final Project
//
// motor.cpp
// Teeter
//

#include "motor.hpp"

namespace dev {
namespace motor_1_0 {

Motor::Motor(unsigned int f_pin, unsigned int r_pin, unsigned int s_pin)
    : f_pin(f_pin), r_pin(r_pin), s_pin(s_pin) {
  // empty
}

void Motor::init() const {
  pinMode(f_pin, OUTPUT);
  pinMode(r_pin, OUTPUT);
  pinMode(s_pin, OUTPUT);
}

void Motor::set_speed(int speed) {
  // Manage direction
  if (speed < 0) {
    digitalWrite(f_pin, LOW);
    digitalWrite(r_pin, HIGH);
    speed = -speed;
  } else {
    digitalWrite(f_pin, HIGH);
    digitalWrite(r_pin, LOW);
  }
  // Write pwm value
  analogWrite(s_pin, (speed > 254 ? 255 : speed));
}
}  // namespace motor_1_0
}  // namespace dev
