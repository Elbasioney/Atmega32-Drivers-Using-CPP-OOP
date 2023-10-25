#include <avr/io.h>
#include <util/delay.h>
#include "BIT_MATH.hpp"
#include "DIO.hpp"
#include "INT.hpp"
#include <avr/interrupt.h>

void int0_isr(void);
void int1_isr(void);

DIO dioa6(pina6 , output) ;
DIO dioa7(pina7 , output) ;
DIO diod2(pind2 , input) ;
INT int0(int_0 , rising_edge) ;
INT int1(int_1 , falling_edge) ;
INT int2(int_2 , rising_edge) ;

int main(void){
  int0.interrupt_enable(int0_isr);
  int1.ChangeSenceControl(rising_edge);
  int1.interrupt_enable(int1_isr);
  while(1){
    
  }

  return 0 ; 
}


int count_0 = 0 ;
void int0_isr(void){
  if(count_0 == 0){
    dioa6.write(high);
    count_0++ ; 
  }else{
    dioa6.write(low);  
    count_0 = 0 ; 
  }
 

}

int count_1 = 0 ;
void int1_isr(void){
  if(count_1 == 0){
    dioa7.write(high);
    count_1++ ; 
  }else{
    dioa7.write(low);  
    count_1 = 0 ; 
  }
 

}