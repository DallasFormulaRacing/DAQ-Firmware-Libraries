/*
 * STM32 F4 ADC Peripheral class header file
 * Author:   William Kim
 *
 * Email:    wkim@utdallas.edu
 *
 * (c) 2024 Dallas Formula Racing - Embedded Firmware Team
 * Formula SAE International Collegiate Chapter
 * GPL-3.0 License
 */

#ifndef STM_F4_ADC_STMF4_H
#define STM_F4_ADC_STMF4_H

#include "adc.h" //stm hal dependencies

#include "../../../Interfaces/iadc.hpp" // dfr custom dependencies


namespace platform {
    class AdcStmF4 : public IADC {
        public:
        AdcStmF4(ADC_HandleTypeDef*, DMA_HandleTypeDef*, uint16_t);

        virtual ~AdcStmF4();

        uint16_t convert();

        void write();

        private:
        ADC_HandleTypeDef* hadc;
        DMA_HandleTypeDef* hdma;
        uint16_t pin_;

    };
}


#endif // STM_F4_ADC_STMF4_H
