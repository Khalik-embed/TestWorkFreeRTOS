/*
 * set_get.h
 *
 *  Created on: Mar 22, 2024
 *      Author: outlet
 */

#ifndef MIDDLEWARE_SET_GET_H_
#define MIDDLEWARE_SET_GET_H_

#include "cmsis_os.h"

osThreadId get_set_mem_log_thread_id(osThreadId thread_id);
osThreadId get_set_uart_left_queue_id(osThreadId thread_id);
osThreadId get_set_uart_right_queue_id(osThreadId thread_id);
osThreadId get_set_dispatcher_queue_id(osThreadId thread_id);
osPoolId  get_set_log_pool_id(osPoolId  pool_id_new);
osMessageQId  get_set_log_queue_id(osMessageQId  queue_id_new);

#endif /* MIDDLEWARE_SET_GET_H_ */
