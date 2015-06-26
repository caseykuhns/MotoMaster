/*
 * driver.h
 *
 *  Created on: Apr 1, 2014
 *      Author: caseykuhns
 */

#ifndef DRIVER_H_
#define DRIVER_H_

#define NORMAL 		0
#define TOGGLE 		1
#define NON_INVERT 	2
#define INVERT 		3

#define DIV_0 		0
#define DIV_1 		2
#define DIV_8 		3
#define DIV_64 		4
#define DIV_256		5
#define DIV_1024 	6

#define PWM_PHASE_CORRECT	0
#define PWM_FAST			1

#define PWM_8BIT	1
#define PWM_9BIT	2
#define PWM_10BIT	3

#define CHANNEL1	0
#define CHANNEL2	1

void driverInit(int8_t mode);
void driverSetPower(int8_t channel, int16_t value);

#endif /* DRIVER_H_ */
