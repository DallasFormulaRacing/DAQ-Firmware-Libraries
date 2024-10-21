/**
 * CAN mod packet parser header
 * Author: Will Kim
 * 2024 (c) Dallas Formula Racing
 */

#ifndef CANMODGPS_H
#define CANMODGPS_H

#include <stdint.h>

#include "can.h"

#include "../../Platform/Interfaces/ican.hpp"
#include "../../Platform/STM/F4/CAN/bxcan_stmf4.hpp"

// TAKES A CAN FRAME AS AN ARGUMENT

namespace Sensor
{
    class CANmodGPS
    {
        CANmodGPS(CAN_HandleTypeDef* hcan);
        ~CANmodGPS();

        void receiveFrame();
        void posConvert(const uint64_t frame);
        void imuConvert(const uint64_t frame);
        int pack();
        void transmitData(uint8_t array[]);

        typedef enum { //idk what im gonna use this for
        	GPS_STATUS,
			GPS_TIME,
			GPS_POSITION,
			GPS_ALTITUDE,
			GPS_ATTITUDE,
			GPS_ODOMETER,
			GPS_SPEED,
			GPS_GEOFENCE,
			GPS_IMU
        } GPSOutputSensor;

    private:
        uint8_t posArray[4];
        uint8_t imuArray[7];
        CAN_HandleTypeDef* hcan_;

        // int c = 0b110101010101; # can denote binary numbers with prefix 0b
    };
}

#endif
