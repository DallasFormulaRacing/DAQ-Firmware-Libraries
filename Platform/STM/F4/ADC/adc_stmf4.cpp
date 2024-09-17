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
#include <stdio.h>

namespace platform {
    AdcStmF4::AdcStmF4(ADC_HandleTypeDef* hadc, DMA_HandleTypeDef* hdma) 
    : hadc(hadc), hdma(hdma){
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

        if(HAL_ADC_PollForConversion(hadc,HAL_MAX_DELAY) == HAL_OK)
        {
            return HAL_ADC_GetValue(hadc);
        }

        else {//use during debug
            
            printf("HAL ADC error code: "+HAL_ADC_GetError(hadc));
            HAL_ADC_Stop(hadc);
            return 0x0000; //
        }

    }

    void AdcStmF4::writeToBuffer() //redundant?
    {
        uint16_t ADC_Conversion_Result = convert();

        if( (adc_buf != nullptr) && (adc_buf->size() < buffer_size) )
        {
            adc_buf->push_back(ADC_Conversion_Result);
        }

        else
        {//use during debug
            printf("ADC Buffer Error or Buffer Full\n");
        }
    }
}



