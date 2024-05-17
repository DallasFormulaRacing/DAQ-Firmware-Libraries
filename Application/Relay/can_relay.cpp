/*
 * can_relay.cpp
 *
 *  Created on: May 16, 2024
 *      Author: Nico
 */


#include <cstring>

#include "./Can_Relay.hpp"

namespace application{

	Can_Relay::Can_Relay(std::shared_ptr<platform::ICan> can_bus, CircularQueue<DataPayload>& queue):
		can_bus_(can_bus), queue_(queue){
		rowSize = queue_.GetSize();
		nRows = (queue_.GetSize()%2 == 0) ? queue_.GetSize()/2 : queue_.GetSize()/2 + 1; //This sizing is done with the assumption that all values are floating point
																						 //Each CAN Pay load is 8 bytes = 2 floats

		message = new uint8_t*[nRows];
		for(int i = 0; i < nRows; i++){
			message[i] = new uint8_t[8];
		}
	};

	Can_Relay::~Can_Relay(){
		for(int i = 0; i < nRows; i++){
					delete[] message[i];
				}

				delete[] message;
			}

	void Can_Relay::generate_message(application::DataPayload& data){
		float row[rowSize];
		data.RawRow(row);
		uint8_t message_chunk[8];

		for(int i = 0; i < nRows; i++){
			for(int j = 0; j < 2; j++){
				std::memcpy(message_chunk + (sizeof(float) * j), &row[j + 2 * i], sizeof(float));
			}
			message[i] = message_chunk;
		}

	}

	void Can_Relay::send_message(){
		for(int i = 0; i < nRows; i++){
			can_bus_->Transmit(message[i]);
		}
	}


}
