################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Middleware/parser.c \
../Core/Middleware/set_get.c 

OBJS += \
./Core/Middleware/parser.o \
./Core/Middleware/set_get.o 

C_DEPS += \
./Core/Middleware/parser.d \
./Core/Middleware/set_get.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Middleware/%.o Core/Middleware/%.su Core/Middleware/%.cyclo: ../Core/Middleware/%.c Core/Middleware/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Core/LOG -I../Core/BSP -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Core/Middleware -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Middleware

clean-Core-2f-Middleware:
	-$(RM) ./Core/Middleware/parser.cyclo ./Core/Middleware/parser.d ./Core/Middleware/parser.o ./Core/Middleware/parser.su ./Core/Middleware/set_get.cyclo ./Core/Middleware/set_get.d ./Core/Middleware/set_get.o ./Core/Middleware/set_get.su

.PHONY: clean-Core-2f-Middleware

