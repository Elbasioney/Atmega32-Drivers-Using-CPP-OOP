#include "KEYPAD.hpp"

static const unsigned char characters[4][4] = { {'7', '8', '9', '/'},             // Keypad characters
                                                {'4', '5', '6', '*'},
                                                {'1', '2', '3', '-'},
                                                {'#', '0', '=', '+'}};



KEYPAD::KEYPAD()
{

}

KEYPAD::KEYPAD(pin_t row_1 , pin_t row_2 , pin_t row_3 , pin_t row_4 , pin_t col_1 ,pin_t col_2 , pin_t col_3 , pin_t col_4)
{
    this->rows[0].pin = row_1 ;  this->rows[1].pin = row_2 ;  this->rows[2].pin = row_3 ;  this->rows[3].pin = row_4 ;
    this->cols[0].pin = col_1 ;  this->cols[1].pin = col_2 ;  this->cols[2].pin = col_3 ;  this->cols[3].pin = col_4 ;
    this->rows[0].mode = output ;  this->rows[1].mode = output ;  this->rows[2].mode = output ;  this->rows[3].mode = output ;
    this->cols[0].mode = input ;  this->cols[1].mode = input ;  this->cols[2].mode = input ;  this->cols[3].mode = input ;
    for(int i = 0; i < 4 ; i++){
        pin_direction_init(rows[i].pin, output);
        pin_direction_init(cols[i].pin, input);
    }

}

KEYPAD::~KEYPAD()
{

}

unsigned char KEYPAD::getKey()
{
    bool ret = false  ;
    for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                rows[j].write(0);
            }
            rows[i].write(1);
            for (int x = 0; x < 4; x++) {
                ret = cols[x].read();
                if (ret == true ) {
                    return characters[i][x];
                }else{
                    
                }
            }
    }
    return 0 ;
}