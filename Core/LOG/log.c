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

uint8_t test_string[128]; //////////
uint8_t test_string2[128]; //////////
static char * log_level_string[]= {
	"LOG_INFO",
	"LOG_WARNING",
	"LOG_ERROR"
	};

log_message_t message_item;

uint8_t message_buf[MAX_LOG_INFO_WIDTH];

void log_print(LogLevel_t log_level, const char* message){
	if (log_level >= LOG_LEVEL) {
		uint32_t time_stamp =  bsp_get_time_stamp();
		sprintf((char *)message_item.message, LOG_MESSAGE_TEMPLATE,
	         (unsigned int)time_stamp,
			 log_level_string[log_level], message);
		message_item.size = strlen((char *)message_item.message);
		bsp_print_log(&message_item);
	}
}

void log_print_from_Queue(log_message_t * log_message){
	sprintf(test_string2, "get= %p, %d, \n", log_message,
			log_message->size, log_message->message[0]);
	log_print(LOG_INFO, test_string2);
	//bsp_print_log((log_message_t *)log_message);
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
osPoolId get_set_log_pool_id(osPoolId pool_id_new){
	static osPoolId pool_id = NULL;
	if (pool_id_new != NULL){
		pool_id = pool_id_new;
	}
	return pool_id;
}

osMessageQId get_set_log_queue_id(osMessageQId queue_id_new){
	static osPoolId queue_id = NULL;
	if (queue_id_new != NULL){
		queue_id = queue_id_new;
	}
	return queue_id;
}


uint32_t log_Queue_put(LogLevel_t log_level, const uint8_t * message){
	uint32_t result;
	if (log_level >= LOG_LEVEL) {
		log_message_t    *message_item_ptr;
		message_item_ptr = osPoolAlloc(get_set_log_pool_id(NULL));
		uint32_t time_stamp =  bsp_get_time_stamp();
		sprintf((char *)message_item_ptr->message, LOG_MESSAGE_TEMPLATE,
	         (unsigned int)time_stamp,
			 log_level_string[log_level], message);
		message_item_ptr->size = strlen((char *)message_item_ptr->message);
		sprintf(test_string, "put= %p, %d, %c\n", message_item_ptr,
				message_item_ptr->size, message_item_ptr->message[0]);
		log_print(LOG_INFO, test_string);
		result = (uint32_t)osMessagePut(get_set_log_queue_id(NULL), (uint32_t)message_item_ptr, osWaitForever);
	}
	return result;
}
