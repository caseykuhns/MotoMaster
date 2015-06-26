/*
 * commands.h
 *
 *  Created on: Apr 26, 2014
 *      Author: caseykuhns
 */

#ifndef COMMANDPARSER_H_
#define COMMANDPARSER_H_
#include <avr/io.h>

#include "commands.h"

#define COMMAND_BUFFER_SIZE 81




void commandInit(void);
void restartBuffer(void);
void invalidCommand(void);
int8_t tokenErrorHandler(int8_t badToken, uint8_t currentCommand);
uint8_t commandCheckASCII(char *dataArray);
int16_t ASCIIComandParse(char *dataArray);
int8_t checkTokenTable(char* token, const command_table array[], uint8_t context, uint8_t array_count);


#endif /* COMMANDS_H_ */
