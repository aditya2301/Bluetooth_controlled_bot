/*
 * main.c
 *
 *  Created on: May 8, 2017
 *      Author: gc
 */

#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#define left1 0
#define left2 1
#define right1 2
#define right2 3
#define BR 9600
#define BPS ((F_CPU/(BR*16UL))-1)
uint8_t rxbyte=0;
//void uart_init();
ISR(USART0_RX_vect)
{
	rxbyte=UDR0;
}
void uart_init()
{
	UBRR0H=(uint8_t)(BPS>>8);
	UBRR0L=(uint8_t)(BPS);
			//tx  AND RX
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	sei();   //cli(); for clearing
}
void uart_send(uint8_t senddata)
{
	while((UCSR0A & (1<<UDRE0))==0);
      UDR0=senddata;
}
int main()
{
	DDRC|=((1<<left1)|(1<<left2)|(1<<right1)|(1<<right2));
	uart_init();
	//rxbyte='F';
	while(1)
	{
       if(rxbyte=='F')
       {
    	   PORTC|=(1<<left1);
    	   PORTC&=~(1<<left2);
    	   PORTC|=(1<<right1);
    	   PORTC&=~(1<<right2);
    	   uart_send('F');
    	   _delay_ms(200);

       }
       else if(rxbyte=='B')
       {
    	   PORTC&=~(1<<left1);
    	   PORTC|=(1<<left2);
    	   PORTC&=~(1<<right1);
    	   PORTC|=(1<<right2);
    	   uart_send('B');
    	   _delay_ms(200);

       }
       else if(rxbyte=='L')
              {
           	   PORTC&=~(1<<left1);
           	   PORTC&=~(1<<left2);
           	   PORTC|=(1<<right1);
           	   PORTC&=~(1<<right2);
           	 uart_send('L');
           	_delay_ms(200);

              }
       else if(rxbyte=='R')
              {
           	   PORTC|=(1<<left1);
           	   PORTC&=~(1<<left2);
           	   PORTC&=~(1<<right1);
           	   PORTC&=~(1<<right2);
          // 	uart_send(rxbyte);
           	 uart_send('R');
           	_delay_ms(200);

              }
       else if(rxbyte=='X')
       {
    	   PORTC&=~(1<<left1);
    	   PORTC&=~(1<<left2);
    	   PORTC&=~(1<<right1);
    	   PORTC&=~(1<<right2);
    	   uart_send('X');
    	   _delay_ms(200);
    	  // uart_send(rxbyte);

       }

	}
}

