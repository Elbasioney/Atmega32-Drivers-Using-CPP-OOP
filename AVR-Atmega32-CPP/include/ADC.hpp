#ifndef Adc_H
#define Adc_H

#pragma once

#include <avr/io.h>
#include "BIT_MATH.hpp"



typedef enum{
    channel_0 ,
    channel_1,
    channel_2,
    channel_3,
    channel_4,
    channel_5,
    channel_6,
    channel_7
}Adc_channel_t ; 

typedef enum{
    prescaler_div_by_2 = 0,
    prescaler_div_by_4 = 2,
    prescaler_div_by_8,
    prescaler_div_by_16,
    prescaler_div_by_32,
    prescaler_div_by_64,
    prescaler_div_by_128
}Adc_prescaler_t;

typedef enum{
    AREF = 0,
    AVCC ,
    Internal_2560mv = 3
}voltage_refrence_t;


class Adc
{
public:
    Adc();
    Adc(Adc_channel_t channel);
    int read(Adc_channel_t channel);
    void changeChannel(Adc_channel_t channel);
    ~Adc();
    Adc_channel_t getChannel();
private:
    void init();
    Adc_channel_t c_channel ;
    static const Adc_prescaler_t Adc_prescaler = prescaler_div_by_64 ;
    static const voltage_refrence_t voltage_refrence = AVCC ; 
    friend class LM35 ;
};



#endif