
#include "motor.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

volatile unsigned int dir=0;
volatile unsigned int stop=1;
extern volatile uint64_t count;

#define MOTOR_DELAY 2

void cycle_forward(int cycle)
{
    PORTA = 0xff;
    int i=0;
    for(i = 0; i < cycle*2; i++) 
    {
        
        PORTA = ~(B|D);
        _delay_ms(MOTOR_DELAY);
        PORTA = ~(D|R);
        _delay_ms(MOTOR_DELAY);
        PORTA = ~(R|G);
        _delay_ms(MOTOR_DELAY);
        PORTA = ~(G|B);
        _delay_ms(MOTOR_DELAY);
    }

    PORTA = 0xff;
//    PORTA = 0x0;
}
void cycle_forward2(int cycle)
{
    PORTC = 0xff;
    int i=0;
    for(i = 0; i < cycle*2; i++) 
    {
        PORTC = ~(B|D);
        _delay_ms(MOTOR_DELAY);
        PORTC = ~(D|R);
        _delay_ms(MOTOR_DELAY);
        PORTC = ~(R|G);
        _delay_ms(MOTOR_DELAY);
        PORTC = ~(G|B);
        _delay_ms(MOTOR_DELAY);
    }
    PORTC = 0xff;

}


void cycle_backward(int cycle)
{
    int i=0;
    for(i = 0; i < cycle*2; i++) 
    {
        PORTA = ~(G|B);
        _delay_ms(MOTOR_DELAY);
        PORTA = ~(R|G);
        _delay_ms(MOTOR_DELAY);
        PORTA = ~(D|R);
        _delay_ms(MOTOR_DELAY);
        PORTA = ~(B|D);
        _delay_ms(MOTOR_DELAY);
    }
    PORTA = 0xff;
}
void cycle_backward2(int cycle)
{
    int i=0;
    for(i = 0; i < cycle*2; i++) 
    {
        PORTC = ~(G|B);
        _delay_ms(MOTOR_DELAY);
        PORTC = ~(R|G);
        _delay_ms(MOTOR_DELAY);
        PORTC = ~(D|R);
        _delay_ms(MOTOR_DELAY);
        PORTC = ~(B|D);
        _delay_ms(MOTOR_DELAY);
    }
    PORTC = 0xff;
}

void set_dir(int i)
{

    dir = i;
}

void set_stop()
{
//    printf("Hello Plotter! count is %ld \r\n", count);
    PORTA = 0xff;
    PORTC = 0xff;
    stop = 1;
}

