/*
 * circularBuffer.c
 *
 *  Created on: May 11, 2014
 *      Author: caseykuhns
 */
#include "ringBuffer.h"
#include "serial.h"

uint8_t charBuffer[BUFFER_SIZE];
volatile uint8_t bufferLength;
uint8_t bufferHead;
uint8_t bufferTail;

void putCharInBuffer(uint8_t data){

	if(bufferLength >= BUFFER_SIZE){
		bufferOverflow();
		return;
	}

	charBuffer[bufferTail] = data;
	//Advance the ring buffer tail by 1
	bufferTail++;
	//Add one to the available bytes count
	bufferLength++;
	//Check bufferTail to ensure it does not overflow
	bufferTail = bufferTail % BUFFER_SIZE;
};

uint8_t getCharFromBuffer(void){
	//Check if there is data in the buffer, if not return -1
	if(bufferLength == 0) return -1;
	//return character from buffer
	uint8_t data = charBuffer[bufferHead];
	//Advance the ring buffer head by 1
	bufferHead++;
	//Subtract 1 from the available bytes count
	bufferLength--;
	//Check bufferHead to ensure it does not overflow
	bufferHead = bufferHead % BUFFER_SIZE;
	return data;
}

uint8_t getBufferLength(void){
	return bufferLength;
}

void bufferOverflow(void){
}

void flushBuffer(void){
	bufferHead = 0;
	bufferTail = 0;
	bufferLength = 0;
}
