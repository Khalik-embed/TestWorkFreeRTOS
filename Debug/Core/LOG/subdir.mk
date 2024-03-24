################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/LOG/log.c 

OBJS += \
./Core/LOG/log.o 

C_DEPS += \
./Core/LOG/log.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LOG/%.o Core/LOG/%.su Core/LOG/%.cyclo: ../Core/LOG/%.c Core/LOG/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Core/LOG -I../Core/BSP -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Core/Middleware -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-LOG

clean-Core-2f-LOG:
	-$(RM) ./Core/LOG/log.cyclo ./Core/LOG/log.d ./Core/LOG/log.o ./Core/LOG/log.su

.PHONY: clean-Core-2f-LOG

