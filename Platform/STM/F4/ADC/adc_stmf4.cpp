/*
 * STM32 F4 ADC Peripheral class file
 * Author:   William Kim
 *
 * Email:    wkim@utdallas.edu
 *
 * (c) 2024 Dallas Formula Racing - Embedded Firmware Team
 * Formula SAE International Collegiate Chapter
 * GPL-3.0 License
 */


#include "../../../Interfaces/iadc.hpp" // dfr custom interface
#include "adc_stmf4.hpp" //include header

namespace platform {
    AdcStmF4::AdcStmF4(ADC_HandleTypeDef* hadc, DMA_HandleTypeDef* hdma, uint16_t pin) 
    {
        MX_ADC1_Init();
        HAL_ADC_Init(hadc);
        HAL_DMA_Init(hdma);
    }

    AdcStmF4::~AdcStmF4()
    {
        HAL_ADC_DeInit(hadc);
        HAL_DMA_DeInit(hdma);
    }

    uint16_t AdcStmF4::convert()
    {
        HAL_ADC_Start(hadc);

        uint16_t value = HAL_ADC_GetValue(hadc);
    }

    

    void AdcStmF4::write()
    {

    }
}



