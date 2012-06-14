/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <util/delay.h>
//#define R (1<<6)
//#define B (1<<4)
//#define Y (1<<2)
//#define W (1<<0)

#define B (1<<6)
#define G (1<<4)
#define R (1<<2)
#define D (1<<0)
//#define B ~(1<<6)
//#define G ~(1<<4)
//#define R ~(1<<2)
//#define D ~(1<<0)

int main(void)
{
    DDRA = 0xff;
    PORTA = 0;
    /* insert your hardware initialization here */
    for(;;){
//        PORTA = B|D;
//        _delay_ms(10);
//        PORTA = D|R;
//        _delay_ms(10);
//        PORTA = R|G;
//        _delay_ms(10);
//        PORTA = G|B;
//        _delay_ms(10);

        PORTA = ~(B|D);
        _delay_ms(2);
        PORTA = ~(D|R);
        _delay_ms(2);
        PORTA = ~(R|G);
        _delay_ms(2);
        PORTA = ~(G|B);
        _delay_ms(2);
        /* insert your main loop code here */
    }
    return 0;   /* never reached */
}
