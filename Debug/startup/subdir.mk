################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32f072.s 

OBJS += \
./startup/startup_stm32f072.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo %cd%
	arm-none-eabi-as -mcpu=cortex-m0 -mthumb -mfloat-abi=soft -I"C:/Users/Ilja-NP/workspace/stm32f072b-disco_stdperiph_lib" -I"C:/Users/Ilja-NP/Google Drive/Uni/WiSe 16_17/RFE/Projektarbeit/MicroMouse/inc" -I"C:/Users/Ilja-NP/workspace/stm32f072b-disco_stdperiph_lib/CMSIS/core" -I"C:/Users/Ilja-NP/workspace/stm32f072b-disco_stdperiph_lib/CMSIS/device" -I"C:/Users/Ilja-NP/workspace/stm32f072b-disco_stdperiph_lib/StdPeriph_Driver/inc" -I"C:/Users/Ilja-NP/workspace/stm32f072b-disco_stdperiph_lib/Utilities/STM32F072B-Discovery" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


