//
// AEP 3630 Final Project
//
// motor.hpp
// Teeter
//

#ifndef TEETER_MOTOR_HPP_
#define TEETER_MOTOR_HPP_

#include <Arduino.h>

namespace dev {
inline namespace motor_1_0 {
/** Class representing a simple motor driver that allows speed control. **/
class Motor {
 public:
  /** General motor constructor. **/
  Motor(unsigned int f_pin, unsigned int r_pin, unsigned int s_pin);
  /** Initializes the pin modes for this motor. **/
  void init() const;
  /** Sends a signed speed command to the motor. Uses 8 bit PWM so this function
   *  clamps inputs to the range [-255,255]. **/
  void set_speed(int speed);

 private:
  // Forward and reverse H bridge gpio input pins
  unsigned int const f_pin;
  unsigned int const r_pin;
  // Speed H bridge PWM input pin
  unsigned int const s_pin;
};

}  // namespace motor_1_0
}  // namespace dev

#endif
