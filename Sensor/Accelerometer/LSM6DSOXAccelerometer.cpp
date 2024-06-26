/*
* Accelerometer LSM6DSOX
* Authors:       William Lim
*
* Email:         wll180000@utdallas.edu
*
* (c) 2023 Dallas Formula Racing - Embedded Firmware Team
* Formula SAE International Collegiate Chapter
* GPL-3.0 License
*/
// Standard Libraries
#include <stdint.h>
#include <cmath>
#include <limits>

// DFR Custom dependencies
#include "LSM6DSOXAccelerometer.hpp"



namespace sensor{

LSM6DSOX_Accelerometer::LSM6DSOX_Accelerometer(I2C_HandleTypeDef& hi2c):i2c_(hi2c){}

void LSM6DSOX_Accelerometer::init() {
    static constexpr uint8_t kNumBytes = 2;
    uint8_t commands[kNumBytes] = {0};

    // data rate 104hz
    commands[0] = CTRL1_XL;
    commands[1] = 0x40; // 0b01000000
    HAL_I2C_Master_Transmit(&i2c_,LSM6DSOX_ACCELEROMETER_ADDRESS, commands,kNumBytes, HAL_MAX_DELAY);

    calibrate();
}

void LSM6DSOX_Accelerometer::calibrate() {
    static constexpr uint8_t kSampleCount = 100;
    double acc_magnitude = 0;
    double average_array[kSampleCount];

    // Collects samples to calibrate for 1G
    for(int i = 0; i < kSampleCount; i++) {
        ReadRawAcceleration();
        acc_magnitude = sqrt(raw_acceleration_data_[0] * raw_acceleration_data_[0] + raw_acceleration_data_[1] * raw_acceleration_data_[1] + raw_acceleration_data_[2] * raw_acceleration_data_[2]);
        average_array[i] = acc_magnitude * 0.001;
    }

    double min_value = std::numeric_limits<double>::max();
    double max_value = -1;

    // Find the largest and smallest magnitudes
    for(int j = 2; j < kSampleCount; j++) {
        if(average_array[j] <= min_value) {
            min_value = average_array[j];

        } else if (average_array[j] > max_value) {
            max_value = average_array[j];
        }
    }

    // Check that the maximum deviation is below a certain threshold.
    // If it is too large, the conversion factor will be set to a previously
    // determined conversion factor
    gravity_adjustment_conversion_factor_ = 0;

    if (max_value - min_value < 0.09) {
        double total_array = 0;
	    for(int i = 0; i < kSampleCount; i++) {
		    total_array += average_array[i];
	    }

	    gravity_adjustment_conversion_factor_ = total_array / kSampleCount;
    } else {
        // Testing found that ~1.028 is about 1G
        gravity_adjustment_conversion_factor_ = 1.028;
    }

}

void LSM6DSOX_Accelerometer::SetODR(ODR ODRValue){
	static constexpr uint8_t kNumBytes = 2;
    uint8_t commands[kNumBytes] = {0};
    commands[0] = CTRL1_XL;
    uint8_t currentRegisterValue[1] = {0};

    // read the current register values for the CTRL_X register
	HAL_I2C_Master_Transmit(&i2c_,LSM6DSOX_ACCELEROMETER_ADDRESS, commands,1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&i2c_,LSM6DSOX_ACCELEROMETER_ADDRESS, currentRegisterValue,1, HAL_MAX_DELAY);

	// set the ODR bits to the desired value without touching the other bits in the register
	// ODRValue is shifter 4 bits to properly align the desired ODR bits to the proper bits in the register
	commands[1] = (currentRegisterValue[0] & 0x0F) | static_cast<uint8_t>(ODRValue) << 4;

	// write to register with the desired bit values
	HAL_I2C_Master_Transmit(&i2c_,LSM6DSOX_ACCELEROMETER_ADDRESS, commands,kNumBytes, HAL_MAX_DELAY);

}

void LSM6DSOX_Accelerometer::SetFSR(FSR FSRValue){

	static constexpr uint8_t kNumBytes = 2;
    uint8_t commands[kNumBytes] = {0};
    commands[0] = CTRL1_XL;
    uint8_t currentRegisterValue[1] = {0};

    // read the current register values for the CTRL1_XL register
	HAL_I2C_Master_Transmit(&i2c_,LSM6DSOX_ACCELEROMETER_ADDRESS, commands,1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(&i2c_,LSM6DSOX_ACCELEROMETER_ADDRESS, currentRegisterValue,1, HAL_MAX_DELAY);

	// set the FSR bits to the desired value without touching the other bits in the register
	// FSRValue is shifted to properly align the FSR bits in to the register.
	commands[1] = (currentRegisterValue[0] & 0xF3) | static_cast<uint8_t>(FSRValue) << 2  ;

	// write to register with the desired bit values
	HAL_I2C_Master_Transmit(&i2c_,LSM6DSOX_ACCELEROMETER_ADDRESS, commands,kNumBytes, HAL_MAX_DELAY);

	// each FSR has a different sensitivity factor to convert raw data to G
	switch (FSRValue){
	case FSR::FSR2g:
		sensitivity_factor = 0.0000610;
		break;
	case FSR::FSR4g:
		sensitivity_factor = 0.000122;
		break;
	case FSR::FSR8g:
		sensitivity_factor = 0.000244;
		break;
	case FSR::FSR16g:
		sensitivity_factor = 0.000488;
		break;
	}

}

float* LSM6DSOX_Accelerometer::GetAcceleration() {
    return real_acceleration_data_;
}

void LSM6DSOX_Accelerometer::ComputeAcceleration() {
    ReadRawAcceleration();
/*   old calculations for accelerometer
    static constexpr float kMG_LSB = .001F;
    real_acceleration_data_[0] = (raw_acceleration_data_[0]) * kMG_LSB / gravity_adjustment_conversion_factor_;
    real_acceleration_data_[1] = (raw_acceleration_data_[1]) * kMG_LSB / gravity_adjustment_conversion_factor_;
    real_acceleration_data_[2] = (raw_acceleration_data_[2]) * kMG_LSB / gravity_adjustment_conversion_factor_;
*/

    // linearization of the accelerometer. by default range of the accelerometer is ±2 g
    real_acceleration_data_[0] =  sensitivity_factor *raw_acceleration_data_[0] * 9.81;
    real_acceleration_data_[1] =  sensitivity_factor *raw_acceleration_data_[1] * 9.81;
    real_acceleration_data_[2] = (sensitivity_factor *raw_acceleration_data_[2] * 9.81) * (9.81/9.95); // used 9.81/9.9 to further calibrate the z-axis since it was a little bit off
}

void LSM6DSOX_Accelerometer::ReadRawAcceleration() {
	static constexpr int ByteArraySize = 6;
	static constexpr int I2CWriteSize = 1;
	static constexpr int I2CReadSize = 6;

    uint8_t command[1] = { OUTX_L_A };
    HAL_I2C_Master_Transmit(&i2c_,LSM6DSOX_ACCELEROMETER_ADDRESS, command,I2CWriteSize, HAL_MAX_DELAY);

    uint8_t bytes_received[ByteArraySize];
    HAL_I2C_Master_Receive(&i2c_,LSM6DSOX_ACCELEROMETER_ADDRESS, bytes_received,I2CReadSize, HAL_MAX_DELAY);

    // 16-bit values
    raw_acceleration_data_[0] = (bytes_received[1] <<8 | bytes_received[0]);
    raw_acceleration_data_[1] = (bytes_received[3] <<8 | bytes_received[2]);
    raw_acceleration_data_[2] = (bytes_received[5] <<8 | bytes_received[4]);
}

}





