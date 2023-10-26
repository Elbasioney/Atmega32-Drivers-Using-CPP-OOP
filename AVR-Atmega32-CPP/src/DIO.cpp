#include "DIO.hpp"
#include "BIT_MATH.hpp"
#include <avr/io.h>

DIO::DIO(pin_t pin , mode_t mode): pin(pin), mode(mode)
{
    pin_direction_init(pin , mode);
}

DIO::~DIO()
{

}

void DIO::write(bool logic)
{
    int port = this->pin / 8 ;
    int bit = this->pin % 8 ;
    if(this->mode == output){
        switch(port){
            case 0:  if(logic == HIGH){SET_BIT(PORTA, bit) ;}else if(logic == LOW){CLEAR_BIT(PORTA, bit) ;}else{} break;
            case 1:  if(logic == HIGH){SET_BIT(PORTB, bit) ;}else if(logic == LOW){CLEAR_BIT(PORTB, bit) ;}else{} break;
            case 2:  if(logic == HIGH){SET_BIT(PORTC, bit) ;}else if(logic == LOW){CLEAR_BIT(PORTC, bit) ;}else{} break;
            case 3:  if(logic == HIGH){SET_BIT(PORTD, bit) ;}else if(logic == LOW){CLEAR_BIT(PORTD, bit) ;}else{} break;
            default: break ;
        }
    }else{

    }
}

bool DIO::read()
{
    int port = this->pin / 8 ;
    int bit = this->pin % 8 ;
    if(this->mode == input || this->mode == input_pullup){
        switch(port){
            case 0:   return CHECK_BIT(PINA , bit) ;break;
            case 1:   return CHECK_BIT(PINB , bit) ;break;
            case 2:   return CHECK_BIT(PINC , bit) ;break;
            case 3:   return CHECK_BIT(PIND , bit) ;break;
            default: break ;
        }
    }else{
        
    }
    return false ;
}


void DIO::pin_direction_init(pin_t pin , mode_t mode)
{
    int port = pin / 8 ;
    int bit = pin % 8 ;
    switch(port){
        case 0  :  if(mode == output){SET_BIT(DDRA, bit) ;}else if(mode == input){CLEAR_BIT(DDRA, bit);}else if(mode == input_pullup){ CLEAR_BIT(DDRA, bit); SET_BIT(PORTA , bit); }else{} break;
        case 1  :  if(mode == output){SET_BIT(DDRB, bit) ;}else if(mode == input){CLEAR_BIT(DDRB, bit);}else if(mode == input_pullup){ CLEAR_BIT(DDRB, bit); SET_BIT(PORTB , bit); }else{} break;
        case 2  :  if(mode == output){SET_BIT(DDRC, bit) ;}else if(mode == input){CLEAR_BIT(DDRC, bit);}else if(mode == input_pullup){ CLEAR_BIT(DDRC, bit); SET_BIT(PORTC , bit); }else{} break;
        case 3  :  if(mode == output){SET_BIT(DDRD, bit) ;}else if(mode == input){CLEAR_BIT(DDRD, bit);}else if(mode == input_pullup){ CLEAR_BIT(DDRD, bit); SET_BIT(PORTD , bit); }else{} break;
        default :  break ; 
    }
   
}


DIO::DIO()
{
    
}
