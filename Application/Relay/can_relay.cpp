/*
 * can_relay.cpp
 *
 *  Created on: May 16, 2024
 *      Author: Nico
 */
#include "./can_relay.hpp"
namespace application{

	Can_Relay::Can_Relay(std::shared_ptr<platform::ICan> can_bus,
						 CircularQueue<DataPayload> queue):
		can_bus_(can_bus),
		queue_(queue){
		messageSize = 29;
	}

	void Can_Relay::bitSet(float value, uint8_t* byteArray) {
	    std::memcpy(byteArray, &value, sizeof(float));
	    std::reverse(byteArray, byteArray + 4);
	}

	void Can_Relay::Generate_Messages(application::DataPayload data){

		transmission_ended_ = false;
		float message_row[messageSize] = {0};
		uint8_t row;
		uint8_t column;
		data.RawRow(message_row);
		for(int i = 0; i < messageSize; i++){
			row = i/2; //integer division by default floors
			column = (i%2) * 4; //the column which the row goes into is essentially sinusoidal
			bitSet(message_row[i], &message[row][column]);
		}

	}


	void Can_Relay::Send_Messages(){
		for(int i = 0; i < kRows; i++){
			can_bus_->Transmit(message[i]);
			//printf("Sending Message! \n");
		}
	}

	void Can_Relay::End_Transmission(bool logging_flag){
		if(!logging_flag && !transmission_ended_){
			can_bus_->Transmit(kEnd_transmission_);
			transmission_ended_ = true;
		}
	}
}
