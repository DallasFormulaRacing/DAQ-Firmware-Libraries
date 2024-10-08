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

//TAKES A CAN FRAME AS AN ARGUMENT

namespace Sensor {
    class CANmodGPS {
        CANmodGPS(platform::ICan& canInterface);
        ~CANmodGPS();

        int read();
        void posConvert(const uint16_t frame);
        void imuConvert(const uint16_t frame);
        int pack();

        private:
        uint8_t posFrame[4];
        uint8_t imuFrame[7];
        platform::ICan& canInterface;

        //int c = 0b110101010101; # can denote binary numbers with prefix 0b

    };
}


#endif
