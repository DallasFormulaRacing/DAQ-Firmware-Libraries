/*
 * can_relay.cpp
 *
 *  Created on: May 16, 2024
 *      Author: Nico
 */
#include <algorithm>
#include <cstring>
#include "./can_relay.hpp"
namespace application{

	Can_Relay::Can_Relay(std::shared_ptr<platform::ICan> can_bus, CircularQueue<DataPayload> queue):
		can_bus_(can_bus), queue_(queue){
		messageSize = queue_.GetSize();
		nRows = (messageSize%2 == 0) ? messageSize/2 : messageSize/2 + 1; //This sizing is done with the assumption that all values are floating point
																		  //Each CAN Pay load is 8 bytes = 2 floats
		message = new uint8_t*[nRows];
		for(int i = 0; i < nRows; i++){
			message[i] = new uint8_t[8];
		}
	}

	Can_Relay::~Can_Relay(){
		for(int i = 0; i < nRows; i++){
			delete[] message[i];
		}
		delete[] message;
	}

	void Can_Relay::bitSet(float value, uint8_t* byteArray) {
	    std::memcpy(byteArray, &value, sizeof(float));
	    std::reverse(byteArray, byteArray + 4);
	}

	void Can_Relay::Generate_Messages(application::DataPayload data){
		float row[messageSize];
		uint8_t r;
		uint8_t c;
		data.RawRow(row);
		for(int i = 0; i < messageSize; i++){
			r = i/2; //integer division by default floors
			c = (i%2) * 4; //the column which the row goes into is essentially sinusoidal
			bitSet(row[i], &message[r][c]);
		}
	}


	void Can_Relay::Send_Messages(){

		/*if(!queue_.IsEmpty()){
			for(int i = 0; i < nRows; i++){
				can_bus_->Transmit(message[i]);
			}
		}*/

		can_bus_->Transmit(test_data);
	}
}
