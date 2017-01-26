################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/analyzer.c \
../src/board.c \
../src/delay.c \
../src/drehratensensor.c \
../src/lre_gyro.c \
../src/lre_leds.c \
../src/lre_temp.c \
../src/main.c \
../src/maze.c \
../src/move.c \
../src/syscalls.c \
../src/system_stm32f0xx.c \
../src/telemetry.c \
../src/uart.c \
../src/ultraschall.c 

OBJS += \
./src/analyzer.o \
./src/board.o \
./src/delay.o \
./src/drehratensensor.o \
./src/lre_gyro.o \
./src/lre_leds.o \
./src/lre_temp.o \
./src/main.o \
./src/maze.o \
./src/move.o \
./src/syscalls.o \
./src/system_stm32f0xx.o \
./src/telemetry.o \
./src/uart.o \
./src/ultraschall.o 

C_DEPS += \
./src/analyzer.d \
./src/board.d \
./src/delay.d \
./src/drehratensensor.d \
./src/lre_gyro.d \
./src/lre_leds.d \
./src/lre_temp.d \
./src/main.d \
./src/maze.d \
./src/move.d \
./src/syscalls.d \
./src/system_stm32f0xx.d \
./src/telemetry.d \
./src/uart.d \
./src/ultraschall.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32F072B_DISCO -DSTM32F072RBTx -DSTM32F0 -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F072 -I"C:/Users/nemour/Documents/workspace/stm32f072b-disco_stdperiph_lib" -I"C:/Users/nemour/Documents/workspace/MicromouseMain/CMSIS/core" -I"C:/Users/nemour/Documents/workspace/MicromouseMain/inc" -I"C:/Users/nemour/Documents/workspace/stm32f072b-disco_stdperiph_lib/CMSIS/core" -I"C:/Users/nemour/Documents/workspace/stm32f072b-disco_stdperiph_lib/CMSIS/device" -I"C:/Users/nemour/Documents/workspace/stm32f072b-disco_stdperiph_lib/StdPeriph_Driver/inc" -I"C:/Users/nemour/Documents/workspace/stm32f072b-disco_stdperiph_lib/Utilities/STM32F072B-Discovery" -include"C:/Users/nemour/Documents/workspace/stm32f072b-disco_stdperiph_lib/CMSIS/device/stm32f0xx.h" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


