#include <avr/io.h>
#include "uart_communication.h"

void UART_INIT(unsigned int ubrr){
    UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

void UART_Transmit(unsigned char data) {
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void UART_SendString(const char* str) {
	while (*str) {
		UART_Transmit(*str++);
	}
}
