
#ifndef _PLOTTER_UART_H_
#define _PLOTTER_UART_H_
#include <stdio.h>

void uart_init();
int putChar(char data, FILE* f);
void uart_transmit(unsigned char);

#endif
