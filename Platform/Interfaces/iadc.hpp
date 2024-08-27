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
        virtual ~IADC() = 0;
        virtual uint16_t convert() = 0;
        virtual void write() = 0;

    private:


    };
}

#endif