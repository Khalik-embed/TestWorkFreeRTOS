/*
 * time_bsp.c
 *
 *  Created on: Mar 21, 2024
 *      Author: outlet
 */

#include "stm32f1xx_hal.h"

#include "time_bsp.h"

uint32_t bsp_get_time_stamp(void){
	return HAL_GetTick();
}
;
