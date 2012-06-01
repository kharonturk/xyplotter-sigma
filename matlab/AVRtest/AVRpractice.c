#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <string.h>
#include <stdio.h>

/****************************
	start usart
		BAUD 115200
		FOSC 14.7456
****************************/
#define BUFFER_LENGTH 100



/*************************
	global variables
*************************/
unsigned char send = '0';
char buffer[BUFFER_LENGTH];

static FILE myStream = FDEV_SETUP_STREAM(TxChar, RxChar, _FDEV_SETUP_RW);
int a=0, b=0, c=0;


/******************************
	Initialization function
*******************************/
void InitUART(void)
{
	UBRR0L=7;
	UCSR0A|=(1<<UDRE0);
	UCSR0B|=(1<<RXCIE0)|(1<<TXEN0)|(1<<RXEN0);
	UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
}
void InitINT(void)
{
	EICRB |= (1<<ISC70);
	EIMSK |= (1<<INT7);

	EICRB |= (1<<ISC60);
	EIMSK |= (1<<INT6);
}

/***********************
	Functions
***********************/
void TxChar(unsigned char data)
{
	while(!(UCSR0A&(1<<UDRE0)));
	UDR0=data;
}
unsigned char RxChar(void)
{
	while(!(UCSR0A&(1<<RXC0)));
	return UDR0;
}


/*******************************
	main function
*******************************/
int main(void)
{
	InitUART();
	InitINT();
	
	DDRC = 0xff;
	PORTC = 0x00;

	sei();
	while(1){PORTC = (a<<2)|(b<<1)|(c<<0);}

	return 0;
}




/**************************
	interrupt function
***************************/
SIGNAL(SIG_INTERRUPT7)
{
	fprintf(&myStream,"%d\n",1);
}

SIGNAL(SIG_INTERRUPT6)
{
	fprintf(&myStream,"%d\n",2);
	_delay_ms(1);
	fscanf(&myStream, "%d %d %d\n", &a, &b, &c);
}
