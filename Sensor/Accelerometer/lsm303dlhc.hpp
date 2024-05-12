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

#ifndef ACCELEROMETER_LSM303DLHC_H
#define ACCELEROMETER_LSM303DLHC_H

// Standard Libraries
#include <inttypes.h>
#include <vector>
#include <array>
#include <memory>

// DFR Custom Dependancies
#include "iaccelerometer.hpp"
#include "i2c.h"

#define MAG_ADDRESS  0x3C
#define ACC_ADDRESS  0x32

// Register Addresses
#define MR_REG_M          0x02

#define CRA_REG_M         0x00
#define CTRL_REG1_A       0x20
#define CTRL_REG4_A       0x23

#define OUT_X_L_A         0x28
#define OUT_X_H_M         0x03

namespace sensor{

class LSM303DLHC: public IAccelerometer {
    public:
		/// @param hi2c an I2C peripheral from ST's HAL
        LSM303DLHC(std::shared_ptr<platform::II2C> i2c);

        virtual ~LSM303DLHC() = default;

        // Initialize the device
        void init() override;

        // returns the value of the accelerometer at the given moment
        // @return -19.6 to 19.6 (  ±2g  )
        float* GetAcceleration() override;


        // calculates the acceleration in terms of m/s^2
        void ComputeAcceleration() override;


    private:
        // averages the idle value of the accelerometer to calibrate
        void calibrate() override;


        // reads raw values from the accelerometer
        // @return -32768 to 32767
        void ReadRawAcceleration();


        std::shared_ptr<platform::II2C> i2c_;


        // value to hold offset values, scale, and gravity
        int offset_[3];
        int scale_[3];
        float gravity_adjustment_conversion_factor_;


        // data to hold accelerometer values in 16 bit form or in m/s^2 form
        short raw_acceleration_data_[3] = {0, 0, 0};
        float real_acceleration_data_[3] = {0, 0, 0};

};

}
#endif // ACCELEROMETER_LSM303DLHC_H
