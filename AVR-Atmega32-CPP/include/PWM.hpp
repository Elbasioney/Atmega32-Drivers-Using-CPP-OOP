#ifndef PWM_H
#define PWM_H

#pragma once

#include "DIO.hpp"
#include "TMR0.hpp"

typedef enum{
    pwm_timer0 ,  
    pwm_timer1 ,
    pwm_timer2 
}pwm_working_timer_t;

class PWM : public TMR0 , public DIO
{
public:
    PWM();
    PWM(pwm_working_timer_t working_timer);
    void output(unsigned char pulseWidth);
    unsigned char read();
    ~PWM();

private:
    pwm_working_timer_t pwm_working_timer ;
    static const timer0_clock_t c_clock  = sysclk_prescaler_div_by_1024 ; 
    timer0_mode_t c_mode = pwm_mode ;
    static const unsigned long f_cpu = 16000000UL ;   // cpu clock frequency 
    DIO pwm0 ; 
};

#endif