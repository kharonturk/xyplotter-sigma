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
#include "uart.h"
#include "motor.h"
#include "extr.h"



void port_init();

extern volatile uint64_t count;


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
        /* insert your main loop code here */
        printf("%d is interrupt count \r\n", count);
        if( count  > 100 )
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

