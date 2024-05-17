/*
 * can_relay.cpp
 *
 *  Created on: May 16, 2024
 *      Author: Nico
 */



#include "can_relay.hpp"

namespace application{

	void can_relay::generate_message(DataPayload& data, uint8_t* row){
		uint8_t message_chunk[8];

		for(int i = 0; i < nRows; i++){
			for(int j = 0; j < 8; j++){
				message_chunk[j] = row[j + 8 * i];
			}
			message[i] = message_chunk;
		}

	}

	void can_relay::send_message(){
		for(int i = 0; i < nRows; i++){
			can_bus_->Transmit(message[i]);
		}
	}


}
