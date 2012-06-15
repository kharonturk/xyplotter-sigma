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
#define DATA_NUM 1 //The number of data packet : one packet = [1 3] matrix


/*************************
        global variables
*************************/
int arr[100][3];//packer buffer
int idx = 0;//buffer index
char c = 0;


/******************************
        Initialization function
*******************************/
void InitPort(void)
{
	    DDRC = 0xff;//LED
		DDRE = 0x02;//UART & EXTERNAL INTERRUPT
}
void InitUART(void)
{
        UBRR0L=7;
        UCSR0A|=(1<<UDRE0);
        UCSR0B|=(1<<RXCIE0)|(1<<TXEN0)|(1<<RXEN0);
        UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01);
}
void InitINT(void)
{
        EICRB |= (1<<ISC71);
        EIMSK |= (1<<INT7);

        EICRB |= (1<<ISC61);
        EIMSK |= (1<<INT6);

        EICRB |= (1<<ISC51);
        EIMSK |= (1<<INT5);
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

static FILE myStream = FDEV_SETUP_STREAM(TxChar, RxChar, _FDEV_SETUP_RW);

/*******************************
        main function
*******************************/
int main(void)
{
		InitPort();
        InitUART();
        InitINT();	
      
		PORTC = 0xff;//just verify reset
        _delay_ms(50);
        PORTC = 0x00;

        sei();

        while(1);

        return 0;
}

/**************************
        interrupt function
***************************/
SIGNAL(SIG_INTERRUPT7)
{
        fprintf(&myStream,"%c\n",'s');
}

SIGNAL(SIG_INTERRUPT6)
{
	int i=0;
    fprintf(&myStream,"%c\n",'d');

	for(i = 0 ; i < DATA_NUM; i++)
	        fscanf(&myStream, "%d %d %d", &arr[i][0], &arr[i][1], &arr[i][2]);
	idx=0;
}
SIGNAL(SIG_INTERRUPT5)
{
	if(idx < DATA_NUM)
		PORTC = (arr[idx][0]<<0)|(arr[idx][1]<<1)|(arr[idx][2]<<2);
	else
		PORTC = 0x00;
	
	idx++;
}
SIGNAL(SIG_UART0_RECV)
{
	fscanf(&myStream,"%s", &c);
}
