/*
 * serial.h
 *
 *  Created on: Mar 30, 2014
 *      Author: caseykuhns
 */
#ifndef SERIAL_H_
#define SERIAL_H_

#include "baud.h"

void serialInit( uint16_t ubrr);
void serialPutChar(uint8_t data );
void serialPutStr(char *data);
void serialGetChar(void);

#endif
