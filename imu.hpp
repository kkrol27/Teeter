//
// AEP 3630 Final Project
//
// imu.hpp
// Teeter
//

#ifndef TEETER_IMU_HPP_
#define TEETER_IMU_HPP_

#include <Wire.h>

#include "LSM6.h"

inline namespace imu_1_0 {
/** Struct representing a three dimensional vector **/
template <typename T>
struct vector {
  union {
    T a[3];
    struct {
      T x, y, z;
    };
  };
};

extern LSM6 imu;
extern struct vector<float> imu_g;
extern struct vector<float> imu_a;

/** Attempts to initiate the IMU. Will return false if this fails. **/
extern bool init_imu();

/** Reads data from the imu and stores the results of the reading in
 *  imu_g and imu_a is dps and m/s^2. **/
extern void read_imu();

}  // namespace imu_1_0

#endif
