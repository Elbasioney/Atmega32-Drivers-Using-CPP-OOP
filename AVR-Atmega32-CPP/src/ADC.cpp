#include "Adc.hpp"

Adc::~Adc()
{

}

Adc_channel_t Adc::getChannel()
{
    return this->c_channel ;
}

void Adc::init()
{
    
    changeChannel(this->c_channel);              // change channel to the initial channel
    ADMUX &= 0b00111111;                         // ADC voltage reference masking
    ADMUX |= (this->voltage_refrence << 6) ;     // setting ADC voltage reference
    ADCSRA &= 0b11111000;                        // ADC prescaler masking
    ADCSRA |= (this->Adc_prescaler);             // setting ADC prescaler
    SET_BIT(ADCSRA , 7  );                       // Enable ADC
}

Adc::Adc(Adc_channel_t channel)
{
    this->c_channel = channel;
    init();
}

void Adc::changeChannel(Adc_channel_t channel)
{
    ADMUX &= 0b11100000 ;     // Adc MUX masking 
    ADMUX |= channel;         // select Adc channel
}

Adc::Adc()
{
    
}

int Adc::read(Adc_channel_t channel)
{
    this->c_channel = channel ;
    changeChannel(this->c_channel);
    SET_BIT(ADCSRA , 6  );                        // Start channel conversion
    
    int timeout = 10000 ; 
    while(!(ADCSRA & (1 << 4)) && timeout){   // waiting for conversion
        timeout-- ;                           // timeout mechanisms
    }       
    return (int)(ADCL | (ADCH << 8)) ;
    
     
}
