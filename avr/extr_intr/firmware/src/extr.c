
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

volatile uint64_t count;

ISR(INT4_vect)
{
    count++;   
    PORTA = count;
}

void ext_intr_init()
{
    EICRB |= (1<<ISC41) | (1<<ISC40);
    EIMSK |= (1<<INT4);
}
