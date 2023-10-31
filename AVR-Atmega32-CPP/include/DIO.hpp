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


#define LOW  false
#define HIGH true 


class DIO
{
public:
    DIO() ;                          // default constructor
    DIO(pin_t pin , mode_t mode) ;   // DIO paramitrized constructor
    ~DIO();                          // DIO destructor
    void write(bool logic);          // DIO write pin logic 
    bool read();                     // DIO read pin logic
    void on();                       // DIO pin write high
    void off();                      // DIO pin write low
    void toggle();                   // DIO pin toggle
private:
    void pin_direction_init(pin_t pin , mode_t mode);  // DIO direction initialization (output , input , input_pullup)
    pin_t pin ;
    mode_t mode ;
    friend class LCD ;
    friend class KEYPAD ;
    friend class PWM ;
};

#endif










