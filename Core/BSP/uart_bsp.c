/*
 * UartBsp.c
 *
 *  Created on: Mar 20, 2024
 *      Author: outlet
 */
#include "usart.h"

#include "set_get.h"
#include "uart_bsp.h"
#include "bsp.h"

uint8_t uart_left_data[2];
uint8_t uart_right_data[2];
uint8_t uart_disp_data[2];

uint8_t *get_test_data(void){
	return &uart_disp_data;
}

status_t bsp_print_log(log_message_t * message){
	HAL_StatusTypeDef result;
	static log_message_t message_buf;
	message_buf.size = message->size;
	strcpy (message_buf.message, message->message);
	result = HAL_UART_Transmit_IT (&huart1, message_buf.message, message_buf.size);
	if (result == HAL_OK) {

	}
	return result == HAL_OK ? BSP_OK : BSP_ERROR;
}


status_t bsp_transmit_uart_left(uint8_t data_byte){
	HAL_StatusTypeDef result;
	result = HAL_UART_Transmit_IT (&huart2, &data_byte, AMOUNT_OF_BYTES_FOR_ISR_UART_UART_LEFT);
	if (result == HAL_OK) {

	}
	return result == HAL_OK ? BSP_OK : BSP_ERROR;
}

status_t bsp_transmit_uart_right(uint8_t data_byte){
	HAL_StatusTypeDef result;
	result = HAL_UART_Transmit_IT (&huart3, &data_byte, AMOUNT_OF_BYTES_FOR_ISR_UART_UART_RIGHT);
	if (result == HAL_OK) {

	}
	return result == HAL_OK ? BSP_OK : BSP_ERROR;
}



void HAL_UART_TxCpltCallback (UART_HandleTypeDef * huart){
	if (huart->Instance == huart1.Instance){
		osSignalSet(get_set_mem_log_thread_id(NULL), LOG_SIGNAL_TX);
	} else if (huart->Instance == huart2.Instance){
		osSignalSet(get_set_uart_right_queue_id(NULL), UART_RIGHT_SIGNAL_TX);
	} else if (huart->Instance == huart3.Instance){
		osSignalSet(get_set_uart_left_queue_id(NULL), UART_LEFT_SIGNAL_TX);
	}
};

void HAL_UART_RxCpltCallback (UART_HandleTypeDef * huart) {
	if (huart->Instance == huart1.Instance){
		uart_disp_data[1] = uart_disp_data[0];
		HAL_UART_Receive_IT (&huart1, uart_disp_data, AMOUNT_OF_BYTES_FOR_ISR_UART_DISP_LOG);
		osMessagePut(get_set_dispatcher_queue_id(NULL), (uint8_t)uart_disp_data[1], 0x00);
	} else if (huart->Instance == huart2.Instance){
		uart_left_data[1] = uart_left_data[0];
		HAL_UART_Receive_IT (&huart2, uart_left_data, AMOUNT_OF_BYTES_FOR_ISR_UART_UART_LEFT);
		osMessagePut(get_set_uart_left_queue_id(NULL), (uint8_t)uart_left_data[1], 0x00);

	} else if (huart->Instance == huart3.Instance){
		uart_right_data[1] = uart_right_data[0];
		HAL_UART_Receive_IT (&huart3, uart_right_data, AMOUNT_OF_BYTES_FOR_ISR_UART_UART_RIGHT);
		osMessagePut(get_set_uart_right_queue_id(NULL), (uint8_t)uart_right_data[1], 0x00);
	}
}


void init_isr_uarts(void){
	HAL_UART_Receive_IT (&huart1, &uart_disp_data, AMOUNT_OF_BYTES_FOR_ISR_UART_DISP_LOG);
	HAL_UART_Receive_IT (&huart2, &uart_left_data, AMOUNT_OF_BYTES_FOR_ISR_UART_UART_LEFT);
	HAL_UART_Receive_IT (&huart3, &uart_right_data, AMOUNT_OF_BYTES_FOR_ISR_UART_UART_RIGHT);
}

void start_isr_uart_disp(void){
	HAL_UART_Receive_IT (&huart1, &uart_disp_data, AMOUNT_OF_BYTES_FOR_ISR_UART_DISP_LOG);
}
void start_isr_uart_left(void){
	HAL_UART_Receive_IT (&huart2, &uart_left_data, AMOUNT_OF_BYTES_FOR_ISR_UART_UART_LEFT);
}
void start_isr_uart_right(void){
	HAL_UART_Receive_IT (&huart3, &uart_right_data, AMOUNT_OF_BYTES_FOR_ISR_UART_UART_RIGHT);
}
