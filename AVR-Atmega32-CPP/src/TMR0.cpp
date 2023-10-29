#include "TMR0.hpp"

static void (*TMR0_Interrupt_Handler)(void) = NULL ;

static unsigned int register_value = 0 ;

static periodicty_t periodicity_status = none ;

static int prescalers[6] = {0 , 1 , 8 , 64 , 256 , 1024 } ; 

TMR0::TMR0()
{

}

TMR0::TMR0(timer0_mode_t mode)
{
    c_mode = mode;
    tick_time = (long)(prescalers[c_clock] * 1000000) / this->f_cpu ;
    init();
}

TMR0::TMR0(timer0_mode_t mode , timer0_edge_t edge)
{
    c_mode = mode;
    c_edge = edge;
    init();
    
}

void TMR0::delay(int msec)
{
    int times = 0 ;
    if(this->f_cpu == 8000000UL){
        times = msec / 38 ; 
    }else if(this->f_cpu == 16000000UL){
        times = msec / 17 ; 
    } 
     
    while(times--){
        TCNT0 = 0 ;
        while(TCNT0 != 255); 
    }
}


void TMR0::singleInterrupt(unsigned int msec , void (* interrupt_handler)(void))
{
    if(NULL == interrupt_handler){
        
    }else{
        SET_BIT(SREG , 7);           // Enable global interrupt
        TMR0_Interrupt_Handler = interrupt_handler ; 
        register_value =  255 - (unsigned char)msec*1000 / tick_time ;
        TCNT0 = register_value ;
        periodicity_status = asynchronous_single_interrupt ;   // set interrupt to be periodic in each timer overflow
        SET_BIT(TIMSK , 0 ) ;
    }
}

void TMR0::periodicInterrupt(unsigned int msec , void (* interrupt_handler)(void))
{
    
    if(NULL == interrupt_handler){
        
    }else{
        SET_BIT(SREG , 7);                                                   // Enable global interrupt
        TMR0_Interrupt_Handler = interrupt_handler ;                         // passing the (ISR) to the callback function
        register_value =  255 - ((unsigned char)((msec*1000) / tick_time)) ; // setting the timer 0 overflow register value
        TCNT0 = register_value ;                               
        periodicity_status = asynchronous_periodic_interrupt ;               // set interrupt to be periodic in each timer overflow
        SET_BIT(TIMSK , 0 ) ;                                                // Enable timer 0 interrupt
    }
    

}

void TMR0::startCount()
{
    SET_BIT(SREG , 7);                                       // Enable global interrupt
    register_value =  0 ;                                    // set the timer 0 overflow register value
    TCNT0 = register_value ;
    periodicity_status = asynchronous_periodic_interrupt ;   // set interrupt to be periodic in
    SET_BIT(TIMSK , 0 ) ;                                    // Enable timer 0 interrupt
}

void TMR0::stopCount()
{
    TCNT0 = 0 ;
    CLEAR_BIT(TIMSK , 0 ) ;                                    // Enable timer 0 interrupt
}

int TMR0::readCount()
{
    return TCNT0 ; 

}

TMR0::~TMR0()
{
    TCCR0 &= 0b11111000 ;                         // no clock source
}

void TMR0::init()
{
    TCCR0 &= 0b10110111 ;                         // mode masking
    TCCR0 |= (((c_mode >> 1) & 0x01) << 3);       // selecting mode 
    TCCR0 |= ((c_mode & 0x01) << 6);              // selecting mode

    TCCR0 &= 0b11111000 ;                         // clock source masking
                                 // selecting clock source 

    if(c_mode == normal_mode && c_edge){
        c_edge == T0_falling_edge ? TCCR0 |= 6 : TCCR0 |= 7 ;
    }else{
        TCCR0 |= c_clock;
    }
    

}





// TMR0 overflow ISR 
ISR(TIMER0_OVF_vect)
{
    if(TMR0_Interrupt_Handler)
    {
        TMR0_Interrupt_Handler();
    }else{

    }
    if(periodicity_status == asynchronous_periodic_interrupt){
        TCNT0 = register_value ; 
    }else if(periodicity_status == asynchronous_single_interrupt){
        CLEAR_BIT(TIMSK , 0 ) ;
    }else{

    }
    
}

