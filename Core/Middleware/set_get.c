/*
 * set_get.c
 *
 *  Created on: Mar 22, 2024
 *      Author: outlet
 */

#include "set_get.h"

osThreadId get_set_mem_log_thread_id(osThreadId thread_id){
	static osThreadId log_osThreadId;
	if (thread_id != NULL) {
		log_osThreadId = thread_id;
	}
	return log_osThreadId;
}

osThreadId get_set_dispatcher_queue_id(osThreadId queue_id){
	static osThreadId dispatcher_queueId;
	if (queue_id != NULL) {
		dispatcher_queueId = queue_id;
	}
	return dispatcher_queueId;
}

osThreadId get_set_uart_left_queue_id(osThreadId queue_id){
	static osThreadId uart_left_queueId;
	if (queue_id != NULL) {
		uart_left_queueId = queue_id;
	}
	return uart_left_queueId;
}

osThreadId get_set_uart_right_queue_id(osThreadId queue_id){
	static osThreadId uart_right_queueId;
	if (queue_id != NULL) {
		uart_right_queueId = queue_id;
	}
	return uart_right_queueId;
}

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
