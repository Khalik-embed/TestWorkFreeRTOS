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

typedef struct {
    int size;
    const uint8_t * message;
} log_message_t;

#endif /* BSP_BSP_H_ */
