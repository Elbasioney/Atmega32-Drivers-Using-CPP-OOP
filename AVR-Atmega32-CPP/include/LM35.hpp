#ifndef LM35_H
#define LM35_H

#pragma once

#include "ADC.hpp"

class LM35 : public Adc
{
public:
    LM35();
    LM35(Adc_channel_t channel);
    ~LM35();
    int temperatureInCilicus();
    int temperatureInFahrenheit();
    int temperatureInKelvin();
private:
    Adc_channel_t c_channel ;
    static const Adc_prescaler_t Adc_prescaler = prescaler_div_by_64 ;
    static const voltage_refrence_t voltage_refrence = AVCC ; 
};

#endif