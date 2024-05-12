/*
* STM32 F4 I2C Peripheral
* Author:   Nico
*
* (c) 2024 Dallas Formula Racing - Embedded Firmware Team
* Formula SAE International Collegiate Chapter
* GPL-3.0 License
*/

#include <DFR_Libraries/Platform/STM/F4/I2C/i2c_stmf4.hpp>

namespace platform {

	I2CStmF4::I2CStmF4(I2C_HandleTypeDef &hi2c)
			: i2c_(hi2c) {
	}

	I2CStmF4::~I2CStmF4(){}

	void I2CStmF4::Receive(uint8_t *response, uint8_t dev_add_, uint8_t response_size_){
		HAL_I2C_Master_Receive(&i2c_, dev_add_, response, response_size_, HAL_MAX_DELAY);
	}

	void I2CStmF4::Transmit(uint8_t *commands, uint8_t dev_add_, uint8_t maxBytes){
		HAL_I2C_Master_Transmit(&i2c_,dev_add_, commands, maxBytes, HAL_MAX_DELAY);
	}

}

