
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "motor.h"

volatile Motor motorA;


ISR(TIMER0_COMP_vect)
{
    PORTC ^= (1<<0);
}

ISR(TIMER0_OVF_vect)
{
    OCR0 = motorA.speed;
    if( motorA.dir)
    {
        PORTC |= (1<<0);
        PORTC &= ~(1<<2);
    }
    else 
    {
        PORTC &= ~(1<<0);
        PORTC |= (1<<2);
    }
}

void timer_init()
{
    TCCR0 |= (1<<CS02) | (1<<CS01) | (1<<CS00); //clk/1024
    OCR0 = 0;
    TIMSK |= (1<<OCIE0) | (1<<TOIE0);
}

void motor_init()
{
    motorA.dir   = 0;
    motorA.speed = 1;
}

