/*
 * can_relay.hpp
 *
 *  Created on: May 3, 2024
 *      Author: Nico
 */
#ifndef DFR_LIBRARIES_APPLICATION_RELAY_CAN_RELAY_HPP_
#define DFR_LIBRARIES_APPLICATION_RELAY_CAN_RELAY_HPP_
#include <memory>
#include <algorithm>
#include <cstring>

#include "../../Platform/STM/F4/CAN/bxcan_stmf4.hpp"
#include "../../Platform/Interfaces/igpio.hpp"
#include "../circular_queue.hpp"
#include "../data_payload.hpp"

#include <bitset>

namespace application{
	class Can_Relay{
	public:
		Can_Relay(std::shared_ptr<platform::ICan> can_bus,
				  CircularQueue<DataPayload> queue);
		//shared pointer to the can bus to relay and reference to the data queue to get the message
		//allocate memory

		~Can_Relay();

		void Generate_Messages(DataPayload data);

		void Send_Messages();

		void End_Transmission(bool logging_flag);

		void bitSet(float value, uint8_t*);
	private:

		std::shared_ptr<platform::ICan> can_bus_;

		CircularQueue<DataPayload>& queue_;

		uint8_t kEnd_transmission_[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

		static constexpr uint8_t messageSize = 29;

		static constexpr uint8_t kRows = 15;

		bool transmission_ended_ = false;

		uint8_t message[kRows][8] = {0};

		float message_row[messageSize] = {0};
	};
}
#endif /* DFR_LIBRARIES_APPLICATION_RELAY_CAN_RELAY_HPP_ */
