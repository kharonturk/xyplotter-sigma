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
    }
    return 0;   /* never reached */
}
