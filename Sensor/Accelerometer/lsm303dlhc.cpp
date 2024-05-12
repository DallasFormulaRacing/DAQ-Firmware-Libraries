/*
* Accelerometer LSM303DLHC
* Authors:       Nathaniel Ho
*                Cristian Cruz
*                Chad Melhem
*                William Lim
*
* Email:         nathanielho712@gmail.com
*                cris14.alex@gmail.com
*                chad.melhem@utdallas.edu
*                wll180000@utdallas.edu
*
* (c) 2023 Dallas Formula Racing - Embedded Firmware Team
* Formula SAE International Collegiate Chapter
* GPL-3.0 License
*/

#include "lsm303dlhc.hpp"
#include <stdint.h>
#include <cmath>
#include <limits>


namespace sensor{

LSM303DLHC::LSM303DLHC(std::shared_ptr<platform::II2C> i2c)
		: i2c_ (i2c){}

void LSM303DLHC::init() {
    static constexpr uint8_t kNumBytes = 2;
    uint8_t commands[kNumBytes] = {0};

    // init mag
    // continuous conversion mode
    commands[0] = MR_REG_M;
    commands[1] = 0x00;
    i2c_->Transmit(commands,MAG_ADDRESS, kNumBytes);

    // data rate 75hz
    commands[0] = CRA_REG_M;
    commands[1] = 0x18; // 0b00011000
    i2c_->Transmit(commands,MAG_ADDRESS, kNumBytes);

    // init acc
    // data rate 100hz
    commands[0] = CTRL_REG1_A;
    commands[1] = 0x57; // 0b01010111
    i2c_->Transmit(commands,ACC_ADDRESS, kNumBytes);

    // High Resolution mode (HR) enable
    commands[0] = CTRL_REG4_A;
    commands[1] = 0x08; // 0b00001000
    i2c_->Transmit(commands,ACC_ADDRESS, kNumBytes);
}

float* LSM303DLHC::GetAcceleration() {
    return real_acceleration_data_;
}

void LSM303DLHC::ComputeAcceleration() {
    ReadRawAcceleration();

    // linearization of the accelerometer. by default range of the accelerometer is ±2 g
    real_acceleration_data_[0] = 0.0006 * raw_acceleration_data_[0] - 0.0002;
    real_acceleration_data_[1] = 0.0006 * raw_acceleration_data_[1] - 0.0002;
    real_acceleration_data_[2] = 0.0006 * raw_acceleration_data_[2] - 0.0002;
}

void LSM303DLHC::ReadRawAcceleration() {
	static constexpr int ByteArraySize = 6;

    uint8_t command[1] = { OUT_X_L_A | 0x80 };

    i2c_->Transmit(command, ACC_ADDRESS, 1);

    uint8_t bytes_received[ByteArraySize];

    i2c_->Receive(bytes_received, ACC_ADDRESS, ByteArraySize);

    // 16-bit values
    raw_acceleration_data_[0] = (bytes_received[1] <<8 | bytes_received[0]);
    raw_acceleration_data_[1] = (bytes_received[3] <<8 | bytes_received[2]);
    raw_acceleration_data_[2] = (bytes_received[5] <<8 | bytes_received[4]);
}

}





