#include <util/delay.h>
#include "BIT_MATH.hpp"
#include "DIO.hpp"
#include "INT.hpp"
#include "LCD.hpp"
#include "avr/io.h"
#include "ADC.hpp"
#include "LM35.hpp"

int main(void){
  LM35 lm(channel_0);
  LCD lcd(pinc0 , pinc1 , pinc2 , pinc3,pinc4,pinc5);
  lcd.setCursor(0,0);
  lcd.print("Temp=");
  lcd.setCursor(1,0);
  lcd.print("Temp=");
  lcd.setCursor(2,0);
  lcd.print("Temp=");
  while(1){
    lcd.setCursor(0,6);
    lcd.print(lm.temperatureInCilicus());
    lcd.print("C ");
    /*************************************/
    lcd.setCursor(1,6);
    lcd.print(lm.temperatureInFahrenheit());
    lcd.print("F ");
    /*************************************/
    lcd.setCursor(2,6);
    lcd.print(lm.temperatureInKelvin());
    lcd.print("K ");
  }

  return 0 ; 
}
