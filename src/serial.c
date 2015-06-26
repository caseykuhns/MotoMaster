/*
 * serial.c
 *
 *  Created on: Mar 30, 2014
 *      Author: caseykuhns
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "serial.h"
#include "ringBuffer.h"

void serialInit(uint16_t ubrr) {
	// Set baud rate
	UBRR0H = (uint8_t) (ubrr >> 8);
	UBRR0L = (uint8_t) ubrr;
	// Enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	// Set frame format: 8data, 1stop bit
	UCSR0C = (3 << UCSZ00);
	// Enable interrupt for receive
	UCSR0B |= (1 << RXCIE0);
}

void serialPutChar(uint8_t data)
/* Send a byte through the UART to the user device
 * This is a blocking function.  It waits until the data buffer is finished
 * transferring data.
 */
{
	// Wait for empty transmit buffer
	while ( ! ( UCSR0A & (1 << UDRE0)) );

	UDR0 = data;
}

void serialPutStr(char *data){
	uint8_t i = 0;
	while(data[i] != '\0'){
		serialPutChar(data[i]);
		i++;
	}
}

void serialGetChar()
/* Get byte from UART and place in Buffer
 * This function is used within the
 * RX transmit complete interrupt.
 */
{
	//Wait for transfer to be complete
	while (!(UCSR0A & (1 << RXC0)));
	//Put data from UART data register into the ring buffer.
	putCharInBuffer(UDR0);
}

/* We have to rename the ISR labels depending AVR microcontroller used
*	Current options are:
*	m328, m328p, m2560
*/

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
ISR(USART_RX_vect)
#elif defined (__AVR_ATmega2560__)
ISR(USART0_RX_vect)
#endif

/* Interrupt routine for serial receive.
 */
{
	//Wait for transfer to be complete
	while (!(UCSR0A & (1 << RXC0)));
	//Put data from UART data register into the ring buffer.
	putCharInBuffer(UDR0);
	//serialGetChar();  //Grab the byte and put it in the buffer.
};

