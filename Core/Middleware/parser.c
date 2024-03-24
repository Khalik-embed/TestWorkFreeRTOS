/*
 * parser.c
 *
 *  Created on: Mar 22, 2024
 *      Author: outlet
 */

#include "cmsis_os.h"
#include "parser.h"
#include "log.h"
#include "bsp.h"

uint8_t command_line[MAX_LOG_INFO_WIDTH];
uint8_t test_string[40];
status_assembly_t assembly_str_until_end(uint8_t data_byte){
	status_assembly_t result = READING;
	static uint8_t size = 0;
	if ((size < MAX_LOG_INFO_WIDTH)
		&& (data_byte != END_OF_STR)
		&& (data_byte != CR_SYMBOL)
		&& (data_byte != LF_SYMBOL)) {
		command_line[size] = data_byte;
		command_line[size+1] = 0;
		size ++;
	} else if (size == MAX_LOG_INFO_WIDTH){
		size = 0;
	} else {
		result = COMMAND_READY;
		size = 0;
	}
	return result;
}

void read_until_end(uint8_t * data_ptr, osMessageQId queue_id) {
	while(*data_ptr != 0){
		osMessagePut(queue_id, (uint8_t)*data_ptr, osWaitForever);
		data_ptr++;
	}
}


void command_parser(uint8_t data_byte){
	commands_t command;
	uint8_t * data_str_ptr;
	status_assembly_t status_assembly;
	status_assembly = assembly_str_until_end(data_byte);
	//log_Queue_put(LOG_INFO, (uint8_t *)command_line);
	if (status_assembly == COMMAND_READY) {
		//log_Queue_put(LOG_INFO, command_line);
		if (strncmp(command_line, COMMAND_SEND_UART_LEFT, strlen(COMMAND_SEND_UART_LEFT)-1) == 0) {
			log_Queue_put(LOG_INFO, (uint8_t *)"Get command left");
			command = UART_LEFT_SEND;
			data_str_ptr = &command_line[strlen(COMMAND_SEND_UART_LEFT)];
			log_Queue_put(LOG_INFO, (uint8_t *)data_str_ptr);
		} else if (strncmp(command_line, COMMAND_SEND_UART_RIGHT, strlen(COMMAND_SEND_UART_RIGHT)) == 0){
			command = UART_RIGHT_SEND;
			data_str_ptr = &command_line[strlen(COMMAND_SEND_UART_RIGHT)];
		} else {
			command = NO_COMMAND;
		}

		if (command == UART_LEFT_SEND) {
			read_until_end(data_str_ptr, get_set_uart_left_queue_id(NULL));
			log_Queue_put(LOG_INFO, (uint8_t *)"Send left");
		} else if ( command == UART_RIGHT_SEND) {
			read_until_end(data_str_ptr, get_set_uart_right_queue_id(NULL));
		} else{
			log_Queue_put(LOG_ERROR, (uint8_t *)"ERROR PARSE COMMAND");
		}
	}
}
