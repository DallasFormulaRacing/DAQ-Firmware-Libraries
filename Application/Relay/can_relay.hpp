/*
 * can_relay.hpp
 *
 *  Created on: May 3, 2024
 *      Author: Nico
 */
#ifndef DFR_LIBRARIES_APPLICATION_RELAY_CAN_RELAY_HPP_
#define DFR_LIBRARIES_APPLICATION_RELAY_CAN_RELAY_HPP_
#include <memory>
#include "../../Platform/STM/F4/CAN/bxcan_stmf4.hpp"
#include "../circular_queue.hpp"
#include "../data_payload.hpp"
#include <bitset>

namespace application{
	class Can_Relay{
	public:
		Can_Relay(std::shared_ptr<platform::ICan> can_bus, CircularQueue<DataPayload> queue);
		//shared pointer to the can bus to relay and reference to the data queue to get the message
		//allocate memory

		~Can_Relay();

		void Generate_Messages(DataPayload data);

		void Send_Messages();

		void bitSet(float value, uint8_t*);
	private:

		std::shared_ptr<platform::ICan> can_bus_;

		CircularQueue<DataPayload>& queue_;

		uint8_t nRows;

		uint8_t messageSize; // neither this nor the above is super necessary to allocate memory for but I'm a bad programmer

		uint8_t** message;

		uint8_t test_data[8] = "Hello!";
	};
}
#endif /* DFR_LIBRARIES_APPLICATION_RELAY_CAN_RELAY_HPP_ */
