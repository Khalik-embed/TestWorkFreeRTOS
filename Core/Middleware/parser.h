/*
 * parser.h
 *
 *  Created on: Mar 22, 2024
 *      Author: outlet
 */

#ifndef MIDDLEWARE_PARSER_H_
#define MIDDLEWARE_PARSER_H_

#define COMMAND_SEND_UART_LEFT "LEFT SEND:"
#define COMMAND_SEND_UART_RIGHT "RIGHT SEND:"

#define END_OF_STR (uint8_t)0x0
#define CR_SYMBOL (uint8_t)0xd
#define LF_SYMBOL (uint8_t)0xa
typedef enum {
	READING  = 0,
	COMMAND_READY = 1
}status_assembly_t;

typedef enum {
	UART_LEFT_SEND  = 0,
	UART_RIGHT_SEND = 1,
	NO_COMMAND = 2
}commands_t;

void command_parser(uint8_t data_byte);

#endif /* MIDDLEWARE_PARSER_H_ */
