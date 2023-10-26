#include <util/delay.h>
#include "BIT_MATH.hpp"
#include "DIO.hpp"
#include "INT.hpp"
#include "LCD.hpp"
#include "avr/io.h"

char customChar1[8] = {
	0b00110,
	0b00100,
	0b01110,
	0b00000,
	0b00100,
	0b00100,
	0b00100,
	0b00100
};
char customChar2[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b01100,
	0b00010,
	0b11111,
	0b00000,
	0b00000
};
char customChar3[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b01110,
	0b11011,
	0b01110,
	0b00000
};
char customChar4[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b00100,
	0b00100,
	0b11111,
	0b00000,
	0b00000
};
int main(void){
  
  LCD lcd1(pina0, pina1, pina2, pina3, pina4, pina5, pina6 , pina7, pind0 , pind1);
  lcd1.blinkOn();
  
  lcd1.createCustomCharacter(customChar1 , 0);
  lcd1.createCustomCharacter(customChar2 , 1);
  lcd1.createCustomCharacter(customChar3 , 2);
  lcd1.createCustomCharacter(customChar4 , 3);
  lcd1.printCustomCharacter(3);
  lcd1.printCustomCharacter(2);
  lcd1.printCustomCharacter(1);
  lcd1.printCustomCharacter(0);
  while(1){

  }

  return 0 ; 
}

