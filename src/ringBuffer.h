/*
 * circularBuffer.h
 *
 *  Created on: Apr 27, 2014
 *      Author: caseykuhns
 */

#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_
#include <avr/io.h>

#define BUFFER_SIZE 16

//
void bufferInit(uint8_t size);

//put a character into the buffer
void putCharInBuffer(uint8_t data);
//pull a character from the buffer
uint8_t getCharFromBuffer(void);
//get the current length of the buffer
uint8_t getBufferLength(void);
//helper function to report buffer overflow
void bufferOverflow(void);
//flush buffer
void flushBuffer(void);

#endif /* CIRCULARBUFFER_H_ */
