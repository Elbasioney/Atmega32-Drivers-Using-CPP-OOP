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
  
 	LCD lcd2(pinc0, pinc1, pinc2, pinc3, pinc4, pinc5, pinc6 , pind7, pind2 , pind3);
  	LCD lcd1(pina4, pina5, pina6 , pina7, pind0 , pind1);
  	DIO ledb5(pinb5 , input_pullup );
	lcd1.print("my name is ahmed");
	lcd2.print("i'm ");
	int age = 22 ;
	lcd2.print(age);
	lcd2.print(" years old");
	
  while(1){
  }

  return 0 ; 
}

