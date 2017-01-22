/*
 * main.c
 *
 *  Created on: 21.01.2017
 *      Author: Ilja-NP
 */



#include "common.h"
#include "uart.h"
#include "board.h"
#include "servo.h"


int main(void)
{
	Board_init_gpio();
	Board_enable_timers();
	UART_init();
	UART_enable_interrupt();

	while(1)
	{
	    // wait half a second
		waitForSysTicks(50);

		TIM_SetCompare1(TIM17, 1000);
		TIM_SetCompare1(TIM16, 1000);
	}

}
