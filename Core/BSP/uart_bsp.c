/*
 * UartBsp.c
 *
 *  Created on: Mar 20, 2024
 *      Author: outlet
 */
#include "usart.h"

#include "uart_bsp.h"
#include "bsp.h"

status_t bsp_print_log(log_message_t * message){
	HAL_StatusTypeDef result;
	result = HAL_UART_Transmit_IT (&huart1, message->message, message->size);
	if (result == HAL_OK) {

	}
	return result == HAL_OK ? BSP_OK : BSP_ERROR;
}

osThreadId mem_log_thread_id(osThreadId thread_id){
	static osThreadId log_osThreadId;
	if (thread_id != NULL) {
		log_osThreadId = thread_id;
	}
	return log_osThreadId;
}

void HAL_UART_TxCpltCallback (UART_HandleTypeDef * huart){
	if (huart->Instance == huart1.Instance){
		osSignalSet(mem_log_thread_id(NULL), 0x00000001);
	}
};

//void HAL_UART_TxCpltCallback (&huart){
//	if (huart->Instance == huart1.Instance){
//		osSignalSet(mem_log_thread_id(NULL), 0x00000001);
//	}
//};


//status_t bsp_get_data
