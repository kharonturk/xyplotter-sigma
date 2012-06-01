
#ifndef __UART_PLOTTER_H_
#define __UART_PLOTTER_H_

void uart_transmit(unsigned char data);
void uart_init();
int putChar(char data, FILE* f);

#endif
