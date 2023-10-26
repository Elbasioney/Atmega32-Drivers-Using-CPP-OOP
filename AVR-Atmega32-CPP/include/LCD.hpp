#ifndef LCD_H
#define LCD_H
#pragma once

#include "DIO.hpp"
#include <util/delay.h>
#include "BIT_MATH.hpp"
#include <stdio.h>

typedef enum{
    lcd_4bit_mode = 0 ,
    lcd_8bit_mode 
}lcd_mode_t;

class LCD : public DIO
{
public:
    LCD(pin_t pin1 , pin_t pin2 , pin_t pin3 , pin_t pin4 , pin_t pin5 ,pin_t pin6 , pin_t pin7 , pin_t pin8 , pin_t en , pin_t rs); // parameterized constructor for 8bit mode
    LCD(pin_t pin1 , pin_t pin2 , pin_t pin3 , pin_t pin4 , pin_t en , pin_t rs);                                                    // parameterized constructor for 4bit mode
    LCD(const LCD &lcd) = delete ;                                      // no copy constructor allowed
    ~LCD();                                                             // Destructor
    void print(const char* string);                                     // lcd print function (char or string)
    void print(int number);                                             // lcd print function (numbers)
    void clear(void);                                                   // lcd clear function
    void setCursor(unsigned char row, unsigned char column);            // lcd change cursor position to the desired row and column
    void blinkOn();                                                     // turning cursor blinking on 
    void blinkOff();                                                    // turning cursor blinking off 
    void cursorRight();                                                 // move cursor to right by one column position 
    void cursorLeft();                                                  // move cursor to left by one column position 
    void createCustomCharacter(char* customCharacter , int mem_pos);    // creating a custom character and save it to the desired memory position
    int getCurrentColumn();                                             // returns the current cursor's column position
    int getCurrentRow();                                                // returns the current cursor's row position
    void printCustomCharacter(int mem_pos);                             // lcd print the created custom character at the desired memory position 
    void cursorOn();                                                    // lcd's cursor displayed
    void cursorOff();                                                   // lcd's cursor not displayed
private:
    DIO data[8] ;                                                       // lcd data pins (only four are used for 4bit mode)
    DIO en ;                                                            // lcd enable pin
    DIO rs ;                                                            // lcd register select pin
    lcd_mode_t mode ;                                                   // contains the lcd mode (4bit mode or 8bit mode)
    int c_row ;                                                         // contains the current cursor's row index
    int c_column ;                                                      // contains the current cursor's column index
    void init(void);                                                    // used to preform the lcd initialization sequence
    void lcd_sendCommand(unsigned  char cmd);                           // used to send a command to the lcd
    void lcd_sendData(unsigned char d);                                 // used to send a data to the lcd
    void lcd_enableSignal(void);                                        // used to send an enable signal to the lcd
};

#endif