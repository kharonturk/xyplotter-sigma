/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "uart.h"
#include "motor.h"
//#define R (1<<6)
//#define B (1<<4)
//#define Y (1<<2)
//#define W (1<<0)

//#define G ~(1<<4)
//#define R ~(1<<2)
//#define D ~(1<<0)


volatile uint64_t count = 0;

int main(void)
{
    DDRA = 0xff;
    PORTA = 0;
    DDRD = 0b11111000;
    uart_init();
    printf("Hello Plotter!\r\n");

    sei();

    for(;;){
//        PORTA = B|D;
//        _delay_ms(10);
//        PORTA = D|R;
//        _delay_ms(10);
//        PORTA = R|G;
//        _delay_ms(10);
//        PORTA = G|B;
//        _delay_ms(10);
//
//        _delay_ms(100);
        while(stop) PORTA=0;
        if(dir)
        {
            cycle_forward(100);
        }
        else
        {
            cycle_backward(100);
        }
        count += 1;
        /* insert your main loop code here */
    }
    return 0;   /* never reached */
}
