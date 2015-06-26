/*
 * encoder.h
 *
 *  Created on: Mar 21, 2014
 *      Author: caseykuhns
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define ENCODER1 0
#define ENCODER2 1

#define	LOW_LEVEL 0
#define	ANY_EDGE 1
#define	FALLING 2
#define	RISING 3

void encoderInit(void);
int32_t encoderGet(int8_t channel);

#endif /* ENCODER_H_ */
