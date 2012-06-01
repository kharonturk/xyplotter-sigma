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

#define dir_factor(x) ( (x)? 8:5)

typedef struct motor
{
    unsigned char dir;
    int speed; // 1 is slowest 254 is fastest
} Motor;

void port_init();
void ext_intr_init();
void uart_init();
void timer_init();
void motor_init();
void uart_transmit(unsigned char data);
int putChar(char data, FILE* f);

volatile uint64_t count = 0;
volatile Motor motorA;

ISR(INT4_vect)
{
    count++;   
    PORTA = count;
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

int main(void)
{
    port_init();
    ext_intr_init();
    uart_init();
    timer_init();
    motor_init();
    /* insert your hardware initialization here */
    sei();

    for(;;)
    {
        _delay_ms(100);
    //    printf("%d is interrupt count \r\n", count);
        /* insert your main loop code here */
        printf("%d is interrupt count \r\n", count);
        if( count * dir_factor(motorA.dir) > 100 <<  3)
        {
            count = 0;
            motorA.dir = !motorA.dir;
        }

    }
    return 0;   /* never reached */
}

void port_init()
{
    DDRE &= ~(1<<PE4); // for external interrupt;
    DDRE |= (1<<PE1);  // for uart tx
    DDRE &= ~(1<<PE0); // for uart rx
    DDRA = 0xff;       // for led;
    DDRC = 0xff;       // for motor control
    PORTA = 0;
    PORTC = 0;
}

void ext_intr_init()
{
    EICRB |= (1<<ISC41) | (1<<ISC40);
    EIMSK |= (1<<INT4);
}

void uart_init()
{
    UCSR1B |= (1<<TXEN) | (1<<RXEN) | (1<<RXCIE1);
    UBRR1L = 8;
    fdevopen(putChar,0);
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
