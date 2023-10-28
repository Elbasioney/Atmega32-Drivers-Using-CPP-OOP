#include "LM35.hpp"

LM35::LM35()
{

}

LM35::LM35(Adc_channel_t channel)
{
    this->c_channel = channel;
    init();
}

LM35::~LM35()
{

}

int LM35::temperatureInCilicus()
{
    int adc_reading = read(this->c_channel);
    float calc = ((adc_reading * .00488) * 100 ) ; 
    return (int)calc ;
}

int LM35::temperatureInFahrenheit()
{
    return (int)((temperatureInCilicus() * 9/5.0) + 32) ;
}

int LM35::temperatureInKelvin()
{
    return (int)(temperatureInCilicus() + 273.15) ;
}
