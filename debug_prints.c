#include <avr/io.h>
#include <stdlib.h>

void UART0_init(unsigned int ubrr_value)
{
	UCSR0A = (1 << U2X0);                  // double speed
	UBRR0H = (ubrr_value >> 8);
	UBRR0L = (ubrr_value & 0xFF);
	UCSR0B = (1 << TXEN0);                 // enable transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit, 1 stop bit, no parity
}

void UART0_sendChar(char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

void UART0_sendString(const char *str)
{
	while (*str) UART0_sendChar(*str++);
}

void printSerialStr(const char *str)
{
	UART0_sendString(str);
}

void printSerialStrln(const char *str)
{
	UART0_sendString(str);
	UART0_sendString("\r\n");
}

void printSerialInt(int num)
{
	char buffer[10];
	itoa(num, buffer, 10);
	UART0_sendString(buffer);
}
