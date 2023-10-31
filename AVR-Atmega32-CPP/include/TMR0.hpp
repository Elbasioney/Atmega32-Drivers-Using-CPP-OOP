#ifndef TMR0_H
#define TMR0_H

#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include "BIT_MATH.hpp"
#include <stdio.h>




typedef enum{
    normal_mode = 0 ,
    pwm_mode ,
    ctc_mode ,
    fast_pwm_mode
}timer0_mode_t;

typedef enum{
    sysclk_prescaler_div_by_1 = 1 ,
    sysclk_prescaler_div_by_8 ,
    sysclk_prescaler_div_by_64,
    sysclk_prescaler_div_by_256  = 4 ,
    sysclk_prescaler_div_by_1024 
}timer0_clock_t;


typedef enum{
    T0_falling_edge ,
    T0_rising_edge
}timer0_edge_t;


class TMR0
{
public:
    TMR0();
    TMR0(timer0_mode_t mode );                                                       // for timer mode
    TMR0(timer0_mode_t mode , timer0_edge_t edge);                                   // for counter mode
    void delay(int msec);
    void singleInterrupt(unsigned int msec , void (* interrupt_handler)(void));      // maximum 32 milliseconds on 8MHZ cpu clock frequency
    void periodicInterrupt(unsigned int msec , void (* interrupt_handler)(void));    // maximum 32 milliseconds on 8MHZ cpu clock frequency
    void startCount();                                                               // start counter
    void stopCount();                                                                // stop counter
    int readCount();                                                                 // read counter
    ~TMR0(); 
private:
    timer0_mode_t c_mode ; 
    timer0_edge_t c_edge ;
    static const timer0_clock_t c_clock  = sysclk_prescaler_div_by_1024 ; 
    static const unsigned long f_cpu = 16000000UL ;   // cpu clock frequency 
    long tick_time ; 
    void init();
    friend class PWM ;
};


typedef enum{
    synchronous = 0 ,
    asynchronous_single_interrupt = 1 ,
    asynchronous_periodic_interrupt = 2 ,
    none =  3  
}periodicty_t ;




#endif