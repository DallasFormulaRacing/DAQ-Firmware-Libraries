/*
* STM32 F4 I2C Peripheral
* Author:   Nico
*
* (c) 2024 Dallas Formula Racing - Embedded Firmware Team
* Formula SAE International Collegiate Chapter
* GPL-3.0 License
*/

#ifndef STM_F4_I2C_STMF4_H
#define STM_F4_I2C_STMF4_H

// ST HAL Dependencies
#include "i2c.h"

// DFR Custom Dependencies
#include "../../../Interfaces/ii2c.hpp"


namespace platform{

class I2CStmF4 : public II2C{
public:
	I2CStmF4(I2C_HandleTypeDef &hi2c);

	virtual ~I2CStmF4();

	virtual void Receive(uint8_t* commands, uint8_t dev_add_, uint8_t maxBytes) override;

	virtual void Transmit(uint8_t* response, uint8_t dev_add_, uint8_t response_size) override;

private:
	I2C_HandleTypeDef& i2c_;
};

} // namespace platform

#endif // STM_F4_I2C_STMF4_H
