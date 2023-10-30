#include <util/delay.h>
#include "BIT_MATH.hpp"
#include "DIO.hpp"
#include "INT.hpp"
#include "LCD.hpp"
#include "avr/io.h"
#include "ADC.hpp"
#include "LM35.hpp"
#include "TMR0.hpp"
#include "KEYPAD.hpp"



int main(void){
  KEYPAD pad(pinc0 , pinc1 , pinc2 , pinc3 , pinc4 , pinc5 , pinc6 , pinc7);
  LCD lcd(pina2 , pina3 , pina4 , pina5 , pina1 , pina0);
  lcd.print("Hello, world!");
  lcd.setCursor(1,0);
  unsigned char ret = 0 ;
  while(1){
    ret = pad.getKey() ;
    if(ret){
      lcd.print(ret);
      while(pad.getKey());
      ret = 0 ;
    }else{

    }
    
    
    
  }

  return 0 ; 
}
