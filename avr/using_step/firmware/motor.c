
#include "motor.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

volatile unsigned int dir=0;
volatile unsigned int stop=1;
extern volatile uint64_t count;

void cycle_forward(int cycle)
{
    int i=0;
    for(i = 0; i < cycle; i++) 
    {
        PORTA = ~(B|D);
        _delay_ms(2);
        PORTA = ~(D|R);
        _delay_ms(2);
        PORTA = ~(R|G);
        _delay_ms(2);
        PORTA = ~(G|B);
        _delay_ms(2);
    }

}


void cycle_backward(int cycle)
{
    int i=0;
    for(i = 0; i < cycle; i++) 
    {
        PORTA = ~(G|B);
        _delay_ms(2);
        PORTA = ~(R|G);
        _delay_ms(2);
        PORTA = ~(D|R);
        _delay_ms(2);
        PORTA = ~(B|D);
        _delay_ms(2);
    }
}

void set_dir(int i)
{

    dir = i;
}

void set_stop()
{
    printf("Hello Plotter! count is %ld \r\n", count);
    PORTA = 0;
    stop = 1;
}

