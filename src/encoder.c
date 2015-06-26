/*
 * encoder.c
 *
 *  Created on: Mar 21, 2014
 *      Author: caseykuhns
 */

#include "encoder.h"
#include <avr/io.h>

int32_t encoder_1;
int32_t encoder_2;
/*
int32_t encoderGet(int8_t channel){
	switch(channel){
	case ENCODER1:{
		return encoder_1;
	}
	case ENCODER2:{
		return encoder_2;
	}
	default: return 0;
	}
}

void encoderInit(){
	EIMSK = (1 << INT2)|(1 << INT3)|(1 << INT4)|(1 << INT5);
	EICRA = (ANY_EDGE << ISC20)|(ANY_EDGE << ISC30);
	EICRB = (ANY_EDGE << ISC40)|(ANY_EDGE << ISC50);
}

void encoderUpdate(int8_t encoder){
	static int8_t lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
    static uint8_t enc_val_1 = 0;
    static uint8_t enc_val_2 = 0;

	switch(encoder){
	case ENCODER1 : {
		//Update encoder 1
		enc_val_1 = enc_val_1 << 2;
		enc_val_1 = enc_val_1 | ((PIND & ((1 << PIND2)|(1 << PIND3))) >> 2);
		encoder_1 = encoder_1 + lookup_table[enc_val_1 & 0x0F];
		break;
	}
	case ENCODER2 : {
		//Update encoder 2
		enc_val_2 = enc_val_2 << 2;
		enc_val_2 = enc_val_2 | ((PINE & ((1 << PINE5)|(1 << PINE4))) >> 4);
		encoder_2 = encoder_2 + lookup_table[enc_val_2 & 0x0F];
		break;
	}
	default: break;
	}
}

//Relevant Interrupt Service Routines
ISR(INT2_vect){
	encoderUpdate(ENCODER1);
}
ISR(INT3_vect){
	encoderUpdate(ENCODER1);
}
ISR(INT4_vect){
	encoderUpdate(ENCODER2);
}
ISR(INT5_vect){
	encoderUpdate(ENCODER2);
}


*/
