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



namespace Sensor {
    CANmodGPS::CANmodGPS(platform::ICan &canInterface)
	: canInterface(canInterface) {

    }

    CANmodGPS::~CANmodGPS(){

	}

    int CANmodGPS::read(){
    	return 0;
	}

    void CANmodGPS::posConvert(const uint16_t frame){

	}

    void CANmodGPS::imuConvert(const uint16_t frame){

	}

    int CANmodGPS::pack(){
    	return 0;
	}

    void CANmodGPS::send(uint8_t array[]){

    }

    void binConvert(uint16_t val) {

    }

}
