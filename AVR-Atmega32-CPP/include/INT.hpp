#ifndef INT_H
#define INT_H

#pragma once

typedef enum {
    int_0 = 0 ,
    int_1 ,
    int_2 ,
}int_t;

typedef enum {
    low_level = 0 ,
    on_change ,
    falling_edge ,
    rising_edge 
}sense_t;

class INT
{
public:
    INT(int_t interrupt , sense_t sense);                      // interrupt constructor
    INT(const INT &_int) = delete ;                            // no Copy interrupt constructor allowed
    ~INT();                                                    // interrupt destructor
    void interrupt_disable();                                  // disable interrupt
    void interrupt_enable(void (*interrupt_handler)(void));    // enable interrupt & set callback function
    void ChangeSenceControl(sense_t sense);                    // interrupt trigger mode ( low_level , on_change , falling_edge , rising_edge )
private:
    void init();                                               // set interrupt sense control to the desired initialization
    int_t interrupt ;                                          // interrupt pin number ( int_0 , int_1 , int_2 )
    sense_t sense ;                                            // interrupt trigger mode ( low_level , on_change , falling_edge , rising_edge )
    void (*interrupt_handler)(void);                           // interrupt handler
};

#endif