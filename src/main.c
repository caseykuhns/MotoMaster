/*
 * main.c
 *
 *  Created on: Mar 21, 2014
 *      Author: caseykuhns
 */
#include <avr/io.h>
#include "encoder.h"
#include "serial.h"
#include "baud.h"
#include "driver.h"
#include <util/delay.h>
#include "serial.h"
#include "commandParser.h"
#include <stdlib.h>
#include "parameters.h"

#define BAUD_115200 8

char commandBuffer[COMMAND_BUFFER_SIZE];


//DriverChannel ch0;

void setup(){
	serialInit(BAUD_115200);
	commandInit();
//	encoderInit();
//	driverInit(PWM_10BIT);
	sei();
}

int main(void) {

	setup();
	DDRB = 0xff;
while(1){

		while(commandCheckASCII(commandBuffer) == 0);
		ASCIIComandParse(commandBuffer);
		restartBuffer();
	}

}
