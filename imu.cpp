//
// AEP 3630 Final Project
//
// imu.cpp
// Teeter
//

#include "imu.hpp"

namespace imu_1_0 {

LSM6 imu;

// Gyroscope and accelerometer sensor readings updated by calling read_imu
struct vector<float> imu_g = {
  0.0f, 0.0f, 0.0f
};
struct vector<float> imu_a = {
  0.0f, -9.81f, 0.0f
};

bool init_imu() {
  Wire.begin();
  if (!imu.init()) return false;
  imu.enableDefault();
  return true;
}

// Gyroscope and accelerometer offsets
struct vector<float> const gyr_off = {
  2.841f, -4.335f, -3.708f
};
struct vector<float> const axl_off = {
  0.0f, 0.0f, 0.0f
};

// Exponential filter weights
float const gyr_w = 0.10f;
float const axl_w = 0.10f;

void read_imu() {
  imu.read();
  // Read in data and convert to standard units
  float g[3], a[3];
  g[0] = 250.0f * ((float)imu.g.x) / 32768.0f;
  g[1] = 250.0f * ((float)imu.g.y) / 32768.0f;
  g[2] = 250.0f * ((float)imu.g.z) / 32768.0f;
  a[0] = 2.0f * 9.81f * ((float)imu.a.x) / 32768.0f;
  a[1] = 2.0f * 9.81f * ((float)imu.a.y) / 32768.0f;
  a[2] = 2.0f * 9.81f * ((float)imu.a.z) / 32768.0f;
  // Apply offsets and exponential filters
  for (int i = 0; i < 3; i++) {
    g[i] -= gyr_off.a[i];
    imu_g.a[i] = (1.0f - gyr_w) * g[i] + gyr_w * imu_g.a[i];
    a[i] -= axl_off.a[i];
    imu_a.a[i] = (1.0f - axl_w) * a[i] + axl_w * imu_a.a[i];
  }
}

}  // namespace imu_1_0
