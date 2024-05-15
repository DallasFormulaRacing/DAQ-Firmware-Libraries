/*
 * can_relay.hpp
 *
 *  Created on: May 3, 2024
 *      Author: Nico
 */

#ifndef DFR_LIBRARIES_APPLICATION_RELAY_CAN_RELAY_HPP_
#define DFR_LIBRARIES_APPLICATION_RELAY_CAN_RELAY_HPP_

#include <memory>
#include "../../Platform/CAN/STM/F4/bxcan_stmf4.hpp"
#include "../circular_queue.hpp"
#include "../data_payload.hpp"


namespace application{
	class can_relay{
	public:
		can_relay(std::shared_ptr<platform::ICan> can_bus, CircularQueue<DataPayload>& queue):
			can_bus_(can_bus), queue_(queue){
			nRows = (queue_->GetSize()%8 == 0) ? queue_->GetSize()/8 : queue_->GetSize()/8 + 1;

			message = new uint8_t*[nRows];
			for(int i = 0; i < nRows; i++){
				message[i] = new uint8_t[8];
			}
		};
		//shared pointer to the can bus to relay and reference to the data queue to get the message
		//allocate memory
		~can_relay(){
			for(int i = 0; i < nRows; i++){
				delete[] message[i];
			}

			delete[] message;
		}
		void generate_message(DataPayload& data);

		void send_message();
	private:
		std::shared_ptr<platform::ICan> can_bus_;
		CircularQueue<DataPayload>& queue_;

		constexpr uint8_t nRows;
		uint8_t** message;
	};

}



#endif /* DFR_LIBRARIES_APPLICATION_RELAY_CAN_RELAY_HPP_ */