/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

void port_init();
void ext_intr_init();
void uart_init();
void uart_transmit(unsigned char data);
int putChar(char data, FILE* f);

volatile uint64_t count = 0;

ISR(INT4_vect)
{
    count++;   
}

int main(void)
{
    port_init();
    ext_intr_init();
    uart_init();
    /* insert your hardware initialization here */
    sei();

    for(;;)
    {
        _delay_ms(100);
        printf("%d is interrupt count \r\n", count);
        /* insert your main loop code here */
    }
    return 0;   /* never reached */
}

void port_init()
{
    DDRE &= ~(1<<PE4); // for external interrupt;
    DDRE |= (1<<PE1);  // for uart tx
    DDRE &= ~(1<<PE0); // for uart rx
}

void ext_intr_init()
{
    EICRB |= (1<<ISC41) | (1<<ISC40);
    EIMSK |= (1<<INT4);
}

void uart_init()
{
    UCSR1B |= (1<<TXEN);
    UBRR1L = 8;
    fdevopen(putChar,0);
}

int putChar(char data, FILE* f)
{
    uart_transmit(data);
    return 0;
}

void uart_transmit(unsigned char data)
{
/* Wait for empty transmit buffer */ 
    while ( !( UCSR1A & (1<<UDRE)) )
        ;
/* Put data into buffer, sends the data */ 
    UDR1 = data;
}
