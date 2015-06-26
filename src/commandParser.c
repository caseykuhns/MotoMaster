/*
 * commands.c
 *
 *  Created on: Apr 26, 2014
 *      Author: caseykuhns
 */

#include <avr/io.h>
#include <string.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "commands.h"
#include "commandParser.h"

#include "ringBuffer.h"
#include "serial.h"
#include "errors.h"

uint8_t commandBuffer[COMMAND_BUFFER_SIZE];
uint8_t commandBufferPosition = 0;

//Make a buffer for bringing messages out of program flash.
//This is AVR specific
char progmem_tempBuffer[80];

void commandInit(void){
	//TODO print version number
	serialPutStr("Hello Dave...\n\r");
	restartBuffer();
}

void restartBuffer(void){
	//Reset the command buffer
	commandBufferPosition = 0;
	//Clear the UART buffer just to make sure we don't carry over bad data
	flushBuffer();
	//Give the user a clean fresh input line
	serialPutStr("\r\n> ");
}

void invalidCommand(void){
	serialPutStr("\r\nInvalid command");
	//TODO print help
}

int8_t tokenErrorHandler(int8_t badToken, uint8_t currentCommand){
	//General index Variable
	uint8_t i;
	//Give the print statement a new fresh line to start
	serialPutStr("\r\n");

	//Determine what type of error/status we are working with
	switch(badToken){
	case HELP:{
		if(currentCommand == 0){
			//first level of help mesages.
			for(i = 0; i < (COMMAND_COUNT - 1); i++){
				serialPutStr(" * ");
				serialPutStr(commands[i].commandName);
				serialPutStr(" - ");
				strcpy_P(progmem_tempBuffer, (char*)pgm_read_word(&(commands_help_messages[i])));
				serialPutStr(progmem_tempBuffer);
				serialPutStr("\r\n");
			};
		}
			if(currentCommand >= 1){
				currentCommand--;
				for(i = 0; i < (PARAMETER_COUNT - 1); i++){
					serialPutStr(" * ");
					serialPutStr(parameters[i].commandName);
					serialPutStr(" - ");
					strcpy_P(progmem_tempBuffer, (char*)pgm_read_word(&(parameters_help_messages[i])));
					serialPutStr(progmem_tempBuffer);
					serialPutStr("\r\n");
				}

			}
		break;
	}
	case INVALID_COMMAND:{
		serialPutStr(" INVALID");
		//TODO display contextual help message?
		break;
	}
	case INVALID_CONTEXT:{
		serialPutStr(" NOT AVAILABLE");
		//TODO display contextual help message?
		break;
	}
	default:{ // Catch all other errors (...Cat walks across keyboard)
		serialPutStr(" ERROR");
		break;
	}
	}
	return 0;
}



uint8_t commandCheckASCII(char *dataArray){

	while (getBufferLength() >= 1){

		uint8_t data = getCharFromBuffer();

		if(commandBufferPosition < COMMAND_BUFFER_SIZE){

			if((data >= ' ') && (data <= '~')){
				//Valid text characters
				commandBuffer[commandBufferPosition] = data;
				serialPutChar(data);
				commandBufferPosition++;
			}
		}
		if(data == '\r' || data == '\n'){
			//Return or linefeed
			//CommandComplete
			//Null terminate the string
			if(commandBufferPosition < 1){
				restartBuffer();
				return 0;
			}
			commandBuffer[commandBufferPosition] = 0x00;
			commandBufferPosition = 0;

			return 1;
		}
		if(data == 127){
			//delete
			if(commandBufferPosition > 0){
				serialPutStr("\b \b");
				commandBufferPosition--;
			}
		}
	}
	return 0;
}

int16_t ASCIIComandParse(char *dataArray){

	strlwr(dataArray);  //make everything lower case for easy processing
	char * token;		//create a string to store a token
	uint16_t command = 0;	//store built up command
	int8_t returnedToken;
	uint8_t tokenContext;


	token = strtok(dataArray, " "); //Grab the first token
		//Note: context variable is 0xff since this is the first entry.
	returnedToken = checkTokenTable(token, commands, 0xff, COMMAND_COUNT);
	if(returnedToken < 0){
		return tokenErrorHandler(returnedToken, 0x00);
	}
	command |= returnedToken << COMMAND;
	tokenContext = (1 << returnedToken);

	token = strtok(NULL, " "); //Grab the next token
	returnedToken = checkTokenTable(token, objects, tokenContext, OBJECT_COUNT);
	if(returnedToken < 0){
		return tokenErrorHandler(returnedToken, (command + 1));
	}
	command |= returnedToken << OBJECT;
	tokenContext = (1 << returnedToken << 3);

	token = strtok(NULL, " "); //Grab the next token
	returnedToken = checkTokenTable(token, parameters, tokenContext, PARAMETER_COUNT);
	if(returnedToken < 0){
		return tokenErrorHandler(returnedToken, command);
	}
	command |= returnedToken << PARAMETER;
	tokenContext = (1 << returnedToken);

	if((returnedToken <= PARAMETER_WITH_SUB_PARAMETER - 1) && (returnedToken >= 0)){
		token = strtok(NULL, " "); //Grab the next token
		returnedToken = checkTokenTable(token, sub_parameters, tokenContext, SUB_PARAMETER_COUNT);
		command |= returnedToken << SUB_PARAMETER;
		//if((returnedToken <= SUB_PARAMETER_WITH_SUB_PARAMETER) && (returnedToken >= 0)){
		//	token = strtok(NULL, " "); //Grab the next token
		//	returnedToken = checkTokenTable(token, sub_parameters, tokenContext, SUB_PARAMETER_COUNT);
		//	command |= returnedToken << SUB_PARAMETER;
		//}
	}

#ifdef _DEBUG  //Debug that stuff!!!

	serialPutStr("\n\r");
//
	uint16_t commandTest = command >> COMMAND;
	commandTest &= 0x03;

	serialPutStr(commands[commandTest].commandName);
	serialPutStr(" ");
//
	commandTest = command >> OBJECT;
	commandTest &= 0x07;

	serialPutStr(objects[commandTest].commandName);
	serialPutStr(" ");
//
	commandTest = command >> PARAMETER;
	commandTest &= 0x1F;

	serialPutStr(parameters[commandTest].commandName);
	serialPutStr(" ");
//
	if((commandTest >= 0) && (commandTest <= 2)){

		commandTest = command >> SUB_PARAMETER;
		commandTest &= 0x0F;

		serialPutStr(sub_parameters[commandTest].commandName);
			if((commandTest >= 0) && (commandTest <= 2){
				commandTest = command >> SUB_SUB_PARAMETER;
				commandTest &= 0x0F;
				serialPutStr(sub_sub_parameters[commandTest].commandName);
			}
	}
#endif

	return command;
}


int8_t checkTokenTable(char* token, const command_table array[], uint8_t context, uint8_t array_count){

	uint8_t i; // array index

	for(i=0; i <= (array_count + 1); i++){
		if(i > array_count){
			return INVALID_COMMAND;
		}
		if((strcmp(token, array[i].commandName) == 0)||(strcmp(token, array[i].abreviatedCommandName) == 0)){
			if(i == array_count - 1){
				//print help
				return HELP;
				break;
			}
			if((context & array[i].commandContext) == 0){

				return INVALID_CONTEXT;
				break;
			}
			//If a valid match, break the for loop.
			break;
		}
	}
	return i;
}
