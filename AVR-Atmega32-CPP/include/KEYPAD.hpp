#ifndef KEYPAD_H
#define KEYPAD_H

#pragma once

#include "DIO.hpp"

class KEYPAD : public DIO
{
public:
    KEYPAD();
    KEYPAD(pin_t row_1 , pin_t row_2 , pin_t row_3 , pin_t row_4 , pin_t col_1 ,pin_t col_2 , pin_t col_3 , pin_t col_4);
    ~KEYPAD();
    unsigned char getKey();         // returns the key pressed
private:
    DIO rows[4] ;                   // rows of the keypad
    DIO cols[4] ;                   // columns of the key
};

#endif