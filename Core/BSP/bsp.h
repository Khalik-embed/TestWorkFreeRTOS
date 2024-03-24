/*
 * bsp.h
 *
 *  Created on: Mar 21, 2024
 *      Author: outlet
 */

#ifndef BSP_BSP_H_
#define BSP_BSP_H_

#include <stdint.h>

typedef enum {
	BSP_OK  = 0,
	BSP_ERROR = 1,
	BSP_BUSY= 2,
	BSP_TIMEOUT = 3
}status_t;

#define MAX_LOG_INFO_WIDTH  128
#define LOG_LEVEL LOG_INFO

#define LOG_SIGNAL_TX 0x00000001
#define DISP_SIGNAL_RX 0x00000010

#define UART_LEFT_SIGNAL_TX 0x00000100
#define UART_LEFT_SIGNAL_RX 0x00001000

#define UART_RIGHT_SIGNAL_TX 0x00010000
#define UART_RIGHT_SIGNAL_RX 0x00100000

typedef struct {
    int size;
    uint8_t message[MAX_LOG_INFO_WIDTH];
} log_message_t;

#endif /* BSP_BSP_H_ */
