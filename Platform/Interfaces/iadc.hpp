/*
 * STM32 F4 ADC ABSTRACT INTERFACE
 * Author:   William Kim
 *
 * Email:    wkim@utdallas.edu
 *
 * (c) 2024 Dallas Formula Racing - Embedded Firmware Team
 * Formula SAE International Collegiate Chapter
 * GPL-3.0 License
 */

#ifndef IADC_H
#define IADC_H

#include <cstdint>

namespace platform
{

    class IADC
    {
    public:
        virtual ~IADC() = default;

        virtual void Initialize_ADC() = 0;

        virtual void start() = 0;
        virtual void stop() = 0;

        virtual double read() = 0;

        virtual /* float? */ double Get_ADC_Result() = 0; // retrieve the converted result
    };
}

#endif