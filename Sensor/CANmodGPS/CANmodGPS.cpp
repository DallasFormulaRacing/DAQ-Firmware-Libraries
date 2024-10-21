/*
 * CANMODGPS Function Define
 * Author:   William Kim
 *
 * Email:    wkim@utdallas.edu
 *
 * (c) 2024 Dallas Formula Racing - Embedded Firmware Team
 * Formula SAE International Collegiate Chapter
 * GPL-3.0 License
 */

#include "CANmodGPS.hpp"

#include <cstring>

namespace Sensor
{
    CANmodGPS::CANmodGPS(CAN_HandleTypeDef *hcan)
        : hcan_(hcan) {}

    CANmodGPS::~CANmodGPS() {}

    void CANmodGPS::receiveFrame()
    {
        CAN_RxHeaderTypeDef rxHeader;
        uint8_t rxBuf[8] = {};
        uint64_t rawFrame = 0b0;

        if (HAL_CAN_GetRxMessage(hcan_, CAN_RX_FIFO0, &rxHeader, rxBuf) == HAL_OK)
        {
            memcpy(&rawFrame, rxBuf, sizeof(rxBuf));

            switch (rxHeader.StdId)
            {
            case 0x001: // position can id
                posConvert(rawFrame);
                break;

            case 0x002: // imu can id
                imuConvert(rawFrame);
                break;

            default:
                break;
                /*Write more cases as we include more sensors in firmware*/
            }
        }
    }

    /// @brief 001010 01011010101100110001101001110 1000101101100010111000001101 1
    /// @param frame {6, 29, 28, 1}
    void CANmodGPS::posConvert(const uint64_t frame)
    {
        uint8_t offset = 28 + 29 + 1;

        posArray[0] = (frame >> offset); // accuracy
        offset -= 29;

        posArray[1] = (frame >> offset) & 0x0FFFFFFF; // longitude
        offset -= 28;

        posArray[2] = (frame >> offset) & 0x07FFFFFF; // latitude
        posArray[3] = frame & 1;                      // position valid
    }

    /// @brief 01111011000 10000101000 10000000000 0111111000 1000001000 1000000000 1
    /// @param frame {11, 11, 11, 10, 10, 10, 1}
    void CANmodGPS::imuConvert(const uint64_t frame)
    {
        uint8_t offset = 11 + 11 + 10 + 10 + 10 + 1;

        // ANGULAR VELOCITY ABOUT Z AXIS
        imuArray[0] = (frame >> offset);
        offset -= 11;

        // ANGULAR VELOCITY ABOUT Y AXIS
        imuArray[1] = (frame >> offset & 0x07FF);
        offset -= 11;

        // ANGULAR VELOCITY ABOUT X AXIS
        imuArray[2] = (frame >> offset & 0x07FF);
        offset -= 10;

        // Z AXIS ACCELERATION
        imuArray[3] = (frame >> offset & 0x03FF);
        offset -= 10;

        // Y AXIS ACCELERATION
        imuArray[4] = (frame >> offset & 0x03FF);
        offset -= 10;

        // X AXIS ACCELERATION
        imuArray[5] = (frame >> offset) & 0x03FF;

        // IMU VALID
        imuArray[6] = frame & 1;
    }

    int CANmodGPS::pack()
    {

        return 0;
    }

    void CANmodGPS::transmitData(uint8_t array[])
    {

    }

}
