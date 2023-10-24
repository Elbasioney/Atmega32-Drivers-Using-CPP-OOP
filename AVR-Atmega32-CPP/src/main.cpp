#include <avr/io.h>
#include <util/delay.h>

#include "DIO.hpp"


int main(void){

  DIO dioa6(pina6 , output) ;
  DIO dioa7(pina7 , input_pullup) ;
  
  while(1){
    if(dioa7.read()){
      dioa6.write(low);
    }else{
      dioa6.write(high);
    }
  }

  return 0 ; 
}


