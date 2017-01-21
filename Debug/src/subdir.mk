################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/board.c \
../src/main.c \
../src/syscalls.c \
../src/system_stm32f0xx.c \
../src/uart.c 

OBJS += \
./src/board.o \
./src/main.o \
./src/syscalls.o \
./src/system_stm32f0xx.o \
./src/uart.o 

C_DEPS += \
./src/board.d \
./src/main.d \
./src/syscalls.d \
./src/system_stm32f0xx.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -DSTM32F072B_DISCO -DSTM32F072RBTx -DSTM32F0 -DSTM32 -DDEBUG -DUSE_STDPERIPH_DRIVER -DSTM32F072 -I"C:/Users/Ilja-NP/workspace/stm32f072b-disco_stdperiph_lib" -I"C:/Users/Ilja-NP/Google Drive/Uni/WiSe 16_17/RFE/Projektarbeit/MicroMouse_code/inc" -I"C:/Users/Ilja-NP/workspace/stm32f072b-disco_stdperiph_lib/CMSIS/core" -I"C:/Users/Ilja-NP/workspace/stm32f072b-disco_stdperiph_lib/CMSIS/device" -I"C:/Users/Ilja-NP/workspace/stm32f072b-disco_stdperiph_lib/StdPeriph_Driver/inc" -I"C:/Users/Ilja-NP/workspace/stm32f072b-disco_stdperiph_lib/Utilities/STM32F072B-Discovery" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


