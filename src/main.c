/*
 * main.c
 *
 *  Created on: 21.01.2017
 *      Author: Ilja-NP
 */



#include "common.h"
#include "uart.h"
#include "board.h"


int main(void)
{
	Board_init_gpio();
	UART_init();
	UART_enable_interrupt();
}






