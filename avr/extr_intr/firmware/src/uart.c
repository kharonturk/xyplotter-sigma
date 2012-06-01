
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.h"
#include "motor.h"


extern volatile Motor motorA;

void uart_init()
{
    UCSR1B |= (1<<TXEN) | (1<<RXEN) | (1<<RXCIE1);
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

ISR(USART1_RX_vect)
{
    unsigned char c;
    c = UDR1;

    if( c == '5')
    {
        motorA.speed = 0;
    }
    else if ( c > '5')
        motorA.speed += motorA.dir? 10:-10;
    else
        motorA.speed += motorA.dir? -10:10;

    if( motorA.speed < 0)
    {
        motorA.dir = !motorA.dir;
        motorA.speed = -motorA.speed;
    }
    else if ( motorA.speed > 255)
        motorA.speed = 255;

}

