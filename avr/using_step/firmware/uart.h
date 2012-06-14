
#ifndef _PLOTTER_UART_H_
#define _PLOTTER_UART_H_
#include <stdio.h>

void uart_init();
int putChar(char data, FILE* f);
int getChar(FILE* f);
void uart_transmit(unsigned char);
unsigned char uart_receive();
void uart_rx_intr_enable();
void uart_rx_intr_disable();

#endif
