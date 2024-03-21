/*
 * log.c
 *
 *  Created on: Mar 20, 2024
 *      Author: outlet
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>


#include "cmsis_os.h"

#include "log.h"
#include "time_bsp.h"



static char * log_level_string[]= {
	"LOG_INFO",
	"LOG_WARNING",
	"LOG_ERROR"
	};

uint8_t message_buf[MAX_LOG_INFO_WIDTH];

void log_print(LogLevel_t log_level, const char* message){
	if (log_level >= LOG_LEVEL) {
		uint32_t time_stamp =  bsp_get_time_stamp();
		sprintf((char *)message_buf, LOG_MESSAGE_TEMPLATE,
	         (unsigned int)time_stamp,
			 log_level_string[log_level], message);
		log_message_t message_item = {strlen((char *)message_buf), message_buf};
		bsp_print_log(&message_item);
	}
}

void log_print_from_Queue(osPoolId log_pool, log_message_t * log_message){
	bsp_print_log(log_message);
	osPoolFree(log_pool, log_message);
}

//void AlocMemoryPoolBlockLog (void)  {
//  osPoolId   MemPool_Id;
//  log_message_t *addr;
//
//  if (MemPool_Id != NULL)  {
//    addr = (log_message_t *)osPoolAlloc (MemPool_Id);
//
//    if (addr != NULL) {
//    	log_mem_pool_id(addr);
//    }
//  }
//}
//
//static log_message_t * log_mem_pool_id(log_message_t * new_addr){
//	static log_message_t* addr = NULL;
//	if (new_addr != NULL){
//		addr = new_addr;
//	}
//	return addr;
//}


//void log_Queue_put(LogLevel_t log_level, const char* message, osMessageQId  MsgBox){
//	uint32_t result;
//	if (log_level >= LOG_LEVEL) {
//		log_message_t    *message_item_ptr;
//		uint32_t time_stamp =  bsp_get_time_stamp();
//		sprintf((char *)message_buf, LOG_MESSAGE_TEMPLATE,
//	         (unsigned int)time_stamp,
//			 log_level_string[log_level], message);
//
//		message_item_ptr = osPoolAlloc(log_mem_pool_id(NULL));
//		message_item_ptr->size = strlen((char *)message_buf);
//		message_item_ptr->message = message;
//
//		result = (uint32_t)osMessagePut(MsgBox, (uint32_t)message_item_ptr, osWaitForever);
//
//	}
//	return result;
//}
