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
#include <memory>
#include <vector>

namespace platform
{

    class IADC
    {
    public:
        virtual ~IADC() = 0;

        //adc operations
        virtual uint16_t convert() = 0;
        virtual void write() = 0;

        //buffer mngmt
        virtual void read() = 0;

    private:

    protected:
    std::shared_ptr<std::vector<uint16_t>> adc_buf; //container for adc read
    std::shared_ptr<size_t> buffer_size; //unsigned



    };
}

#endif

//shared pointers buffer and buffer size inside ADCSTMf4
