/*
 * board.c
 *
 *  Created on: 21.01.2017
 *      Author: Ilja-NP
 */

#include "board.h"


void Board_init_gpio()			// Initializes GPIO pins for operation of the peripherals (UART, servo etc.)
{
//**********************************************************
//*  BEGIN UART INIT  **************************************
//**********************************************************
    // ---- initiate USART1 RX (PA10) & TX (PA9) Pin ----
    // (Pin B6 and B7 can be used alternatively; see datasheet table 15, page 44)
    // UART usually uses push pull outputs without pullup or pulldown resistors.
    // Open Drain with pullup resistors would work too
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpioInitStruct1;

    gpioInitStruct1.GPIO_Mode = GPIO_Mode_AF; // the pins have to be bound to USART1 later
    gpioInitStruct1.GPIO_OType = GPIO_OType_PP;
    gpioInitStruct1.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    gpioInitStruct1.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpioInitStruct1.GPIO_Speed = GPIO_Speed_Level_1; // the baud rate is going to be 115200. So 2 MHz on the GPIO is enough<o zhw

    GPIO_Init(GPIOA, &gpioInitStruct1);

    // bind the two Pins to USART1 (see datasheet table 14, p.43)
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

}

void Board_enable_timers()
{
    //**********************************************************
    //*  BEGIN SERVO INIT  *************************************
    //**********************************************************
	TIM_TimeBaseInitTypeDef timerInitStruct;
	TIM_OCInitTypeDef timerOcInitStruct;

	timerInitStruct.TIM_ClockDivision = 0; // no division necessary
	timerInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // timer counts upwards from 0
	// Timer goes for 20 ms,
	timerInitStruct.TIM_Period = 15000; // timer counts only to 20000 and restarts at 0 after that
	// CORECLOCK / (ZIELFREQUENZ - 1)
	timerInitStruct.TIM_Prescaler = SystemCoreClock / (1000000 - 1); // set prescaler, so the timer counts with 1000000 Hz (SystemCoreClock is usually with the STM32F072 48 MHz)
	timerInitStruct.TIM_RepetitionCounter = 0; // set to 0 so the timer repeats forever

	TIM_TimeBaseInit(TIM16, &timerInitStruct);

	// initiate Timer 16's output compare unit
	timerOcInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset; // Pin is low, when the Output is disabled (called idle here)
	timerOcInitStruct.TIM_OCMode = TIM_OCMode_PWM1; // use the PWM1 Mode; Modes are explained in the Reference Manual, page 486 following
	timerOcInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset; // OCN is the inverted output (Low when PB7 is high and vice versa). We don't use this here
	timerOcInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
	timerOcInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; // high means PB9 is high at t_on and low at t_off. Polarity_Low is the inverse
	timerOcInitStruct.TIM_OutputNState = TIM_OutputNState_Disable; // inverted output is not used
	timerOcInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	timerOcInitStruct.TIM_Pulse = 0; // here is the initial t_on time. In this case 1 ms = 1000 s

	// write settings to Timer 16 Channel 1 (each channel has its own function; Channel 3 uses TIM_OC3Init() for example)
	TIM_OC1Init(TIM16, &timerOcInitStruct);
	// PWM Outputs have to be enabled separately on Timer 1, 15, 16 or 17 (see description of the Function TIM_CtrlPWMOutputs)
	TIM_CtrlPWMOutputs(TIM16, ENABLE);

	// Enable the Timer. It starts counting from now on
	TIM_Cmd(TIM16, ENABLE);

	timerInitStruct.TIM_ClockDivision = 0; // no division necessary
	timerInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // timer counts upwards from 0
	// Timer goes for 20 ms,
	timerInitStruct.TIM_Period = 15000; // timer counts only to 20000 and restarts at 0 after that
	// CORECLOCK / (ZIELFREQUENZ - 1)
	timerInitStruct.TIM_Prescaler = SystemCoreClock / (1000000 - 1); // set prescaler, so the timer counts with 1000000 Hz (SystemCoreClock is usually with the STM32F072 48 MHz)
	timerInitStruct.TIM_RepetitionCounter = 0; // set to 0 so the timer repeats forever

	TIM_TimeBaseInit(TIM17, &timerInitStruct);

	// initiate Timer 17's output compare unit
	timerOcInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset; // Pin is low, when the Output is disabled (called idle here)
	timerOcInitStruct.TIM_OCMode = TIM_OCMode_PWM1; // use the PWM1 Mode; Modes are explained in the Reference Manual, page 486 following
	timerOcInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Reset; // OCN is the inverted output (Low when PB7 is high and vice versa). We don't use this here
	timerOcInitStruct.TIM_OCNPolarity = TIM_OCNPolarity_High;
	timerOcInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; // high means PB9 is high at t_on and low at t_off. Polarity_Low is the inverse
	timerOcInitStruct.TIM_OutputNState = TIM_OutputNState_Disable; // inverted output is not used
	timerOcInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	timerOcInitStruct.TIM_Pulse = 0; // here is the initial t_on time. In this case 1 ms = 1000 s

	// write settings to Timer 17 Channel 1 (each channel has its own function; Channel 3 uses TIM_OC3Init() for example)
	TIM_OC1Init(TIM17, &timerOcInitStruct);
	// PWM Outputs have to be enabled separately on Timer 1, 15, 16 or 17 (see description of the Function TIM_CtrlPWMOutputs)
	TIM_CtrlPWMOutputs(TIM17, ENABLE);

	// Enable the Timer. It starts counting from now on
	TIM_Cmd(TIM17, ENABLE);

    //**********************************************************
    //*  BEGIN DREHGEBER INIT  *********************************
    //**********************************************************

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = 40000;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = 500;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &timerInitStructure);
	TIM_Cmd(TIM1, DISABLE);

}



