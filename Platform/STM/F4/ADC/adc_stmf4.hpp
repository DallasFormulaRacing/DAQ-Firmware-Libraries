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
    class AdcStmF4 : public iadc {
        public:
        AdcStmF4(/* ?? */);

        virtual ~AdcStmF4();

        virtual void Initialize_ADC() override;
        
        virtual void start() override;

        virtual void stop() override;

        virtual double read() override;

        virtual double Get_ADC_Result() override;

        private:
        ADC_HandleTypeDef* oo;
        uint16_t pin_;

    }
}


#endif // STM_F4_ADC_STMF4_H
