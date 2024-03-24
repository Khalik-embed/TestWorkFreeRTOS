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

#define AMOUNT_OF_BYTES_FOR_ISR_UART_DISP_LOG (uint16_t)0x1
#define AMOUNT_OF_BYTES_FOR_ISR_UART_LEFT (uint16_t)0x1
#define AMOUNT_OF_BYTES_FOR_ISR_UART_RIGHT (uint16_t)0x1

status_t bsp_print_log(log_message_t * message);
status_t bsp_transmit_uart_right(uint8_t data_byte);
status_t bsp_transmit_uart_left(uint8_t data_byte);
void init_isr_uarts(void);
void start_isr_uart_disp(void);
void start_isr_uart_left(void);
void start_isr_uart_right(void);

#endif /* BSP_UART_BSP_H_ */
