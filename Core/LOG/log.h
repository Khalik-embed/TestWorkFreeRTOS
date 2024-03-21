/*
 * log.h
 *
 *  Created on: Mar 20, 2024
 *      Author: outlet
 */

#ifndef LOG_LOG_H_
#define LOG_LOG_H_



#include "uart_bsp.h"

#define LOG_MESSAGE_TEMPLATE "Time Stamp: %u, Log Level: %s, Message: %s\n"

typedef enum {
	LOG_INFO  = 0,
	LOG_WARNING = 1,
	LOG_ERROR = 2
}LogLevel_t;

void AlocMemoryPoolBlockLog (void);

void log_Queue_put(LogLevel_t log_level, const char* message, osMessageQId  MsgBox);

void log_print(LogLevel_t log_level, const char* message);
void log_print_from_Queue(osPoolId log_pool, log_message_t * log_message);



#endif /* LOG_LOG_H_ */
