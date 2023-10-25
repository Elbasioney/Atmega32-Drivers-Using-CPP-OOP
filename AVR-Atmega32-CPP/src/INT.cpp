#include "INT.hpp"
#include "avr/io.h"
#include "stdlib.h"
#include "BIT_MATH.hpp"
#include <avr/interrupt.h>

static void (*INT0_Interrupt_Handler)(void) = NULL ;
static void (*INT1_Interrupt_Handler)(void) = NULL ;
static void (*INT2_Interrupt_Handler)(void) = NULL ;

INT::INT(int_t interrupt , sense_t sense):interrupt(interrupt),sense(sense)
{
    ChangeSenceControl(sense);   // initialize the interrupt corresponding pin to match the desired configuration
    SET_BIT(SREG , 7);           // Enable global interrupt
}

INT::~INT()
{

}

void INT::interrupt_enable(void (*interrupt_handler)(void))
{
    if(NULL == interrupt_handler){

    }else{
        this->interrupt_handler = interrupt_handler ; 
        switch(this->interrupt){
            case int_0:
                SET_BIT(GICR , 6 );
                INT0_Interrupt_Handler = interrupt_handler;
                break;
            case int_1:
                SET_BIT(GICR , 7 );
                INT1_Interrupt_Handler = interrupt_handler;                
                break;
            case int_2:
                SET_BIT(GICR , 5 );
                INT2_Interrupt_Handler = interrupt_handler;
                break;
            default: 
                break;
    }

}
}

void INT::ChangeSenceControl(sense_t sense)
{
    this->sense = sense ;
    if(this->interrupt == int_0){
        MCUCR &= ~(3 << 0) ;           // int_0 trigger masking
        MCUCR |= (this->sense << 0) ;
    }else if(this->interrupt == int_1){
        MCUCR &= ~(3 << 2) ;           // int_2 trigger masking
        MCUCR |= (this->sense << 2) ;
    }else if(this->interrupt == int_2){
        if(this->sense == falling_edge){
            MCUCSR &= ~(1 << 6) ;      
        }else if(this->sense == rising_edge){
            MCUCSR |=  (1 << 6) ;
        }else{

        }

    }else{


    }
}


/*********************************** ISR for int_0 , int_1 , int_2 ********************************/

ISR(INT0_vect)
{
	if(INT0_Interrupt_Handler){
        INT0_Interrupt_Handler();
    }else{

    }
}

ISR(INT1_vect)
{
	if(INT1_Interrupt_Handler){
        INT1_Interrupt_Handler();
    }else{

    }
}


ISR(INT2_vect)
{
	if(INT2_Interrupt_Handler){
        INT2_Interrupt_Handler();
    }else{

    }
}