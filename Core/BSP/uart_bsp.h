/*
 * UartBsp.h
 *
 *  Created on: Mar 20, 2024
 *      Author: outlet
 */

#ifndef BSP_UART_BSP_H_
#define BSP_UART_BSP_H_

#include "cmsis_os.h"

#include "bsp.h"


status_t bsp_print_log(log_message_t * message);
osThreadId get_set_mem_log_thread_id(osThreadId thread_id);

#endif /* BSP_UART_BSP_H_ */
