
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
    PORTA = 0x0;
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

    PORTA = 0x0;
}
void cycle_forward2(int cycle)
{
    PORTC = 0xff;
    int i=0;
    for(i = 0; i < cycle; i++) 
    {
        PORTC = ~(B|D);
        _delay_ms(2);
        PORTC = ~(D|R);
        _delay_ms(2);
        PORTC = ~(R|G);
        _delay_ms(2);
        PORTC = ~(G|B);
        _delay_ms(2);
    }
    PORTC = 0xff;

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
    PORTA = 0;
}
void cycle_backward2(int cycle)
{
    int i=0;
    for(i = 0; i < cycle; i++) 
    {
        PORTC = ~(G|B);
        _delay_ms(2);
        PORTC = ~(R|G);
        _delay_ms(2);
        PORTC = ~(D|R);
        _delay_ms(2);
        PORTC = ~(B|D);
        _delay_ms(2);
    }
    PORTC = 0xff;
}

void set_dir(int i)
{

    dir = i;
}

void set_stop()
{
    printf("Hello Plotter! count is %ld \r\n", count);
    PORTA = 0;
    PORTC = 0xff;
    stop = 1;
}

