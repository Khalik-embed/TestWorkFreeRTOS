/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "log.h"
#include "bsp.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
osPoolDef (LogMem, 8, log_message_t);
osPoolId  LogMemHandle;
osMessageQDef(LogQueue, 8, uint8_t);
osMessageQId  LogQueue;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId DispatcherTaskHandle;
osThreadId LogTaskHandle;
osThreadId UARTLeftTaskHandle;
osThreadId UARTRightTaskHandle;
osMessageQId LogQueueHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDispacherTask(void const * argument);
void StartLogTask(void const * argument);
void StartUARTLeftTask(void const * argument);
void StartUARTRightTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of LogQueue */

  LogQueueHandle = osMessageCreate(osMessageQ(LogQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of DispatcherTask */
  osThreadDef(DispatcherTask, StartDispacherTask, osPriorityNormal, 0, 256);
  DispatcherTaskHandle = osThreadCreate(osThread(DispatcherTask), NULL);

  /* definition and creation of LogTask */
  osThreadDef(LogTask, StartLogTask, osPriorityLow, 0, 512);
  LogTaskHandle = osThreadCreate(osThread(LogTask), NULL);

  /* definition and creation of UARTLeftTask */
  osThreadDef(UARTLeftTask, StartUARTLeftTask, osPriorityLow, 0, 128);
  UARTLeftTaskHandle = osThreadCreate(osThread(UARTLeftTask), NULL);

  /* definition and creation of UARTRightTask */
  osThreadDef(UARTRightTask, StartUARTRightTask, osPriorityLow, 0, 128);
  UARTRightTaskHandle = osThreadCreate(osThread(UARTRightTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  LogMemHandle = osPoolCreate(osPool(LogMem));
//	if (LogMemHandle != NULL){
//		log_print(LOG_INFO, "POOL INIT");
//	} else {
//		log_print(LOG_ERROR, "POOL DOES NOT INIT");
//	}
  get_set_mem_log_thread_id(LogTaskHandle);
  get_set_log_pool_id(LogMemHandle);
  get_set_log_queue_id(LogQueueHandle);
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDispacherTask */
/**
  * @brief  Function implementing the DispatcherTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDispacherTask */
void StartDispacherTask(void const * argument)
{
  /* USER CODE BEGIN StartDispacherTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(2000);
//    log_print(LOG_INFO, "Dispather task");
    log_Queue_put(LOG_INFO, (uint8_t *)"It is work");
  }
  /* USER CODE END StartDispacherTask */
}

/* USER CODE BEGIN Header_StartLogTask */
/**
* @brief Function implementing the LogTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLogTask */
void StartLogTask(void const * argument)
{
  /* USER CODE BEGIN StartLogTask */
	osEvent  evt1;
	osEvent  evt2;


//	evt2 = osSignalWait (0x00000001, 0x00000FFF);
//    if (evt2.status == osEventSignal){
//    	log_print(LOG_INFO, "Like this");
//    	//log_print_from_Queue(LogMem, evt1.value.p);
//    }
  /* Infinite loop */
  for(;;)
  {
	evt1 = osMessageGet(LogQueueHandle, osWaitForever);
	osDelay(200);
    if (evt1.status == osEventMessage) {
    	log_print_from_Queue(evt1.value.p);
    }
    //log_print(LOG_INFO, "Here1");
    evt2 = osSignalWait (0x00000001, osWaitForever);
    //log_print(LOG_INFO, "Here2");
    if(evt2.status == osEventSignal){
    	osPoolFree(LogMemHandle, evt1.value.p);
    }
  }
  /* USER CODE END StartLogTask */
}

/* USER CODE BEGIN Header_StartUARTLeftTask */
/**
* @brief Function implementing the UARTLeftTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartUARTLeftTask */
void StartUARTLeftTask(void const * argument)
{
  /* USER CODE BEGIN StartUARTLeftTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartUARTLeftTask */
}

/* USER CODE BEGIN Header_StartUARTRightTask */
/**
* @brief Function implementing the UARTRightTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartUARTRightTask */
void StartUARTRightTask(void const * argument)
{
  /* USER CODE BEGIN StartUARTRightTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartUARTRightTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

