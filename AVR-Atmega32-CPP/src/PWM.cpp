#include "PWM.hpp"

static unsigned char PWM0_compare_value = NULL ;

PWM::PWM()
{

}

PWM::PWM(pwm_working_timer_t working_timer)
{
    this->pwm_working_timer = working_timer;
    switch (this->pwm_working_timer){
        case pwm_timer0 :
            SET_BIT(SREG , 7);
            TCCR0 &= 0b10110111 ;                          // mode masking
            TCCR0 |= (((c_mode >> 1) & 0x01) << 3);        // selecting mode 
            TCCR0 |= ((c_mode & 0x01) << 6);               // selecting mode
            TCCR0 &= 0b11111000 ;                          // clock source masking
            TCCR0 |= c_clock ;                             // selecting clock source
        break;

        default : break ; 
    }
}

void PWM::output(unsigned char pulseWidth)
{
    switch (this->pwm_working_timer){
        case pwm_timer0 :
            unsigned char ocr0_value = (unsigned char)((unsigned short)(pulseWidth * 255) / 100 );
            PWM0_compare_value = ocr0_value ;
            CLEAR_BIT(TIMSK , 1);   // Disable on comapre interrupt
            pwm0.pin = pinb3 ;     pwm0.mode = 1 ; 
            pin_direction_init(pwm0.pin , pwm0.mode);
            CLEAR_BIT(TCCR0 , 4 ); 
            SET_BIT(TCCR0 , 5 ) ; 
            OCR0 = PWM0_compare_value ;
            SET_BIT(TIMSK , 1);    // Enable on comapre interrupt
        break;

        default : break ; 

    }
    
    
}

PWM::~PWM()
{

}


ISR(TIMER0_COMPA_vect){
    // Interrupt service routine for compare match A
    OCR0 = PWM0_compare_value ; 
}