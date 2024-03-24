################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/BSP/bsp.c \
../Core/BSP/time_bsp.c \
../Core/BSP/uart_bsp.c 

OBJS += \
./Core/BSP/bsp.o \
./Core/BSP/time_bsp.o \
./Core/BSP/uart_bsp.o 

C_DEPS += \
./Core/BSP/bsp.d \
./Core/BSP/time_bsp.d \
./Core/BSP/uart_bsp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/BSP/%.o Core/BSP/%.su Core/BSP/%.cyclo: ../Core/BSP/%.c Core/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Core/LOG -I../Core/BSP -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Core/Middleware -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-BSP

clean-Core-2f-BSP:
	-$(RM) ./Core/BSP/bsp.cyclo ./Core/BSP/bsp.d ./Core/BSP/bsp.o ./Core/BSP/bsp.su ./Core/BSP/time_bsp.cyclo ./Core/BSP/time_bsp.d ./Core/BSP/time_bsp.o ./Core/BSP/time_bsp.su ./Core/BSP/uart_bsp.cyclo ./Core/BSP/uart_bsp.d ./Core/BSP/uart_bsp.o ./Core/BSP/uart_bsp.su

.PHONY: clean-Core-2f-BSP

