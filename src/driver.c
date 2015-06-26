/*
 * driver.c
 *
 *  Created on: Apr 1, 2014
 *      Author: caseykuhns
 */

#include <avr/io.h>
#include "driver.h"
/*
void driverInit(int8_t mode){

	TCCR3A = (NON_INVERT << COM3A0)|(mode << WGM30);
	TCCR3B = (DIV_1 << CS30)|(PWM_FAST << WGM32);

	TCCR4A = (NON_INVERT << COM4A0)|(mode << WGM40);
	TCCR4B = (DIV_1 << CS40)|(PWM_FAST << WGM42);

	DDRH |= (1 << PINH3)|(1 << PINH4)|(1 << PINH5)|(1 << PINH6);
	DDRG |= (1 << PING5);
	DDRE |= (1 << PINE3);
}

void driverSetPower(int8_t channel, int16_t value){
	switch(channel){
	case CHANNEL1:{
		if(value < 0){
			//reverse direction
			PORTH &= ~(1 << PINH5);
			PORTH |= (1 << PINH4);
			value = 0xFFFF - value;
		}
		else if(value > 0){
			//forward direction
			PORTH &= ~(1 << PINH4);
			PORTH |= (1 << PINH5);
		}
		else {
			PORTH &= ~((1 << PINH5)|(1 << PINH4));
			//Brake
		};

		OCR3A = value & 0x03FF; //Block top 2 bits
		break;
	}
	case CHANNEL2:{

		if(value < 0){
			PORTH &= ~(1 << PINH6);
			PORTG |= (1 << PING5);
			value = 0xFFFF - value;
			//reverse direction
		}
		else if(value > 0){
			PORTH |= (1 << PINH6);
			PORTG &= ~(1 << PING5);
			//forward direction
		}
		else{
			PORTH &= ~(1 << PINH6);
			PORTG &= ~(1 << PING5);
			//Brake
		}

		OCR4A = value & 0x03FF; //Block top 2 bits
		break;
	}
	default: break;
	}
}

*/

