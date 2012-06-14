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
#include "state.h"


volatile uint64_t count = 0;

int main(void)
{
    DDRA = 0xff;
    DDRC = 0xff;
    PORTA=0x0;
    PORTC = 0xff;
    PORTA = 0;
    DDRD = 0b11111000;
    uart_init();
    
    initialize_state();
    printf("Hello Plotter!\r\n");

    sei();

    for(;;){
        Cur->main_loop();
    }
    return 0;   /* never reached */
}
