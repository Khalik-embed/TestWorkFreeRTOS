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
#include "parser.h"
#include "set_get.h"
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
osMessageQId UartLeftHandle;
osMessageQId UartRightHandle;
osMessageQId DispQueueHandle;

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
  osMessageQDef(LogQueue, 8, uint32_t);
  LogQueueHandle = osMessageCreate(osMessageQ(LogQueue), NULL);

  /* definition and creation of UartLeft */
  osMessageQDef(UartLeft, 128, uint8_t);
  UartLeftHandle = osMessageCreate(osMessageQ(UartLeft), NULL);

  /* definition and creation of UartRight */
  osMessageQDef(UartRight, 128, uint8_t);
  UartRightHandle = osMessageCreate(osMessageQ(UartRight), NULL);

  /* definition and creation of DispQueue */
  osMessageQDef(DispQueue, 128, uint8_t);
  DispQueueHandle = osMessageCreate(osMessageQ(DispQueue), NULL);

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
  get_set_log_pool_id(LogMemHandle);

  get_set_log_queue_id(LogQueueHandle);
  get_set_dispatcher_queue_id(DispQueueHandle);
  get_set_uart_left_queue_id(UartLeftHandle);
  get_set_uart_right_queue_id(UartRightHandle);

  get_set_mem_log_thread_id(LogTaskHandle);
  get_set_uart_left_thread_id(UARTLeftTaskHandle);
  get_set_uart_right_thread_id(UARTRightTaskHandle);

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
	osEvent  queue_evt;
	init_isr_uarts();
	log_Queue_put(LOG_INFO, (uint8_t *)" ");
	log_Queue_put(LOG_INFO, (uint8_t *)"Start work, you can send:");
	log_Queue_put(LOG_INFO, (uint8_t *)"LEFT SEND:\"SOME_DATA\"");
	log_Queue_put(LOG_INFO, (uint8_t *)"RIGHT SEND:\"SOME_DATA\"");
  /* Infinite loop */
  for(;;)
  {
	queue_evt = osMessageGet(DispQueueHandle, osWaitForever);
	if (queue_evt.status == osEventMessage){
		command_parser((uint8_t)queue_evt.value.p);
	}
	//osThreadYield();
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
	osEvent  queue_evt;
	osEvent  signal_evt;

  /* Infinite loop */
  for(;;)
  {
	  queue_evt = osMessageGet(LogQueueHandle, osWaitForever);
    if (queue_evt.status == osEventMessage) {
    	log_print_from_Queue(queue_evt.value.p);
    }
    signal_evt = osSignalWait (LOG_SIGNAL_TX, osWaitForever);
    if(signal_evt.status == osEventSignal){
    	osPoolFree(LogMemHandle, queue_evt.value.p);
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
	static uint8_t test_str[50];
	status_t result;
	osEvent  queue_evt;
  /* Infinite loop */
  for(;;)
  {
	 queue_evt = osMessageGet(UartLeftHandle, osWaitForever);
	 if (queue_evt.status == osEventMessage){
		 result = bsp_transmit_uart_right((uint8_t)queue_evt.value.p);
	  	  if (result == BSP_OK) {
	  		sprintf(test_str, " OK GET DATA LEFT=%x", (uint32_t)queue_evt.value.p);
	  	  }else {
	  		sprintf(test_str, "FALL GET DATA LEFT=%x", (uint32_t)queue_evt.value.p);
	  	  }

	  	  log_Queue_put(LOG_INFO, test_str);
	  }
	 osSignalWait (UART_RIGHT_SIGNAL_TX, osWaitForever); // wait until send

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
	static uint8_t test_str[50];
	status_t result;
	osEvent  queue_evt;
  /* Infinite loop */
  for(;;)
  {
	  queue_evt = osMessageGet(UartRightHandle, osWaitForever);
	  if (queue_evt.status == osEventMessage){
		  	  result = bsp_transmit_uart_left((uint8_t)queue_evt.value.p);
		  	  if (result == BSP_OK) {
		  		sprintf(test_str, " OK GET DATA RIGHT=%x", (uint32_t)queue_evt.value.p);
		  	  }else {
		  		sprintf(test_str, "FALL GET DATA RIGHT=%x", (uint32_t)queue_evt.value.p);
		  	  }

		  	  log_Queue_put(LOG_INFO, test_str);
		  }
	  osSignalWait (UART_LEFT_SIGNAL_TX, osWaitForever); // wait until send
  }
  /* USER CODE END StartUARTRightTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

