// DFR_Libraries/Sensor/IMU/imu.cpp
#include "imu.hpp"

namespace sensor {

LSM6DSOX_IMU::LSM6DSOX_IMU(I2C_HandleTypeDef &hi2c)
    : gyroscope_(hi2c), accelerometer_(hi2c) {
}

void LSM6DSOX_IMU::Initialize() {
    gyroscope_.SetODR(LSM6DSOX_Gyroscope::ODR::ODR104);
    gyroscope_.SetFSR(LSM6DSOX_Gyroscope::FSR::DPS500);
    accelerometer_.SetODR(LSM6DSOX_Accelerometer::ODR::ODR104);
    accelerometer_.SetFSR(LSM6DSOX_Accelerometer::FSR::FSR2g);
}

void LSM6DSOX_IMU::init() {
    accelerometer_.init();
}

void LSM6DSOX_IMU::calibrate() {
    accelerometer_.CalibrateSensor();  // Use the public wrapper method to access private method
}
void LSM6DSOX_IMU::ComputeAcceleration() {
    accelerometer_.ComputeAcceleration();
}

float* LSM6DSOX_IMU::GetAcceleration() {
    return accelerometer_.GetAcceleration();
}

short* LSM6DSOX_IMU::DegreesPerSecond() {
    return gyroscope_.DegreesPerSecond();
}

float* LSM6DSOX_IMU::RadiansPerSecond() {
    return gyroscope_.RadiansPerSecond();
}

void LSM6DSOX_IMU::updateSensorData() {
    accelerometer_.ComputeAcceleration();
    gyroscope_.GetAngularVelocity();  // Use the public wrapper method to access private method
    for (int i = 0; i < 3; ++i) {
        acceleration_[i] = accelerometer_.GetAcceleration()[i];
        angular_velocity_[i] = gyroscope_.DegreesPerSecond()[i] * gyroscope_.GetDegreesToRadians();  // Use the public wrapper method
    }
}
}
