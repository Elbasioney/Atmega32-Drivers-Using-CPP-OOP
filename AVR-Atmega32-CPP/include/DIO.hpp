#ifndef DIO_H
#define DIO_H

#pragma once

typedef enum{
    pina0 = 0 ,
    pina1 ,
    pina2 ,
    pina3 ,
    pina4 ,
    pina5 ,
    pina6 ,
    pina7 ,
    pinb0 ,
    pinb1,
    pinb2,
    pinb3,
    pinb4,
    pinb5,
    pinb6,
    pinb7,
    pinc0,
    pinc1,
    pinc2,
    pinc3,
    pinc4,
    pinc5,
    pinc6,
    pinc7,
    pind0,
    pind1,
    pind2,
    pind3,
    pind4,
    pind5,
    pind6,
    pind7
}pin_t; 


typedef enum{
    input = 0 ,
    output ,
    input_pullup
}mode_t;

typedef enum{
    low ,
    high 
}logic_t;

class DIO
{
public:
    DIO(pin_t pin , mode_t mode) ;   // DIO constructor
    DIO(const DIO &dio) = delete ;   // DIO copy constructor
    ~DIO();                          // DIO destructor
    void write(logic_t logic);       // DIO write pin logic 
    logic_t read();                  // DIO read pin logic
private:
    void pin_direction_init(pin_t pin , mode_t mode);  // DIO direction initialization (output , input , input_pullup)
    pin_t pin ;
    mode_t mode ;
};

#endif










