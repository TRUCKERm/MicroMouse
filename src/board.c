/*
 * board.c
 *
 *  Created on: 21.01.2017
 *      Author: Ilja-NP
 */
#include "common.h"
#include "board.h"


void Board_init_gpio()			// Initializes GPIO pins for operation of the peripherals (UART, servo etc.)
{
//**********************************************************
//*BEGIN UART INIT  ****************************************
//**********************************************
    // ---- initiate USART1 RX (PA10) & TX (PA9) Pin ----
    // (Pin B6 and B7 can be used alternatively; see datasheet table 15, page 44)
    // UART usually uses push pull outputs without pullup or pulldown resistors.
    // Open Drain with pullup resistors would work too
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpioInitStruct;

    gpioInitStruct.GPIO_Mode = GPIO_Mode_AF; // the pins have to be bound to USART1 later
    gpioInitStruct.GPIO_OType = GPIO_OType_PP;
    gpioInitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
    gpioInitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpioInitStruct.GPIO_Speed = GPIO_Speed_Level_1; // the baud rate is going to be 115200. So 2 MHz on the GPIO is enough<o zhw

    GPIO_Init(GPIOA, &gpioInitStruct);

    // bind the two Pins to USART1 (see datasheet table 14, p.43)
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
}
