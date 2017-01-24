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
#include "delay.h"

char uartBuffer[50];
uint32_t elapsedtime[10];
uint32_t run_counter = 0;
uint16_t interrupt_count = 0;
uint16_t avg = 0;

int main(void)
{
	Board_init_gpio();
	Board_enable_timers();
	UART_init();
	UART_enable_interrupt();
	systickInit(1000);


	while(1)
	{
	    // wait half a second
		waitForSysTicks(50);

		TIM_SetCompare1(TIM17, 50);
		TIM_SetCompare1(TIM16, 1700);
	}
}

void EXTI2_3_IRQHandler(void) {

    // always clear the pending bit
    EXTI_ClearITPendingBit(EXTI_Line2);

    // because we only us line 11, we don't have to check for other lines generating the interrupt
    if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)) {
        // save the present counter value as rising edge time
  //      soundTravelingTime = TIM_GetCounter(TIM16);
    	TIM_Cmd(TIM6,ENABLE);
    	interrupt_count++;

    	if ((interrupt_count >= 1) && (TIM_GetCounter(TIM6) > 50))
    	{
//    		TIM_Cmd(TIM6,DISABLE);
    		elapsedtime[run_counter] = TIM_GetCounter(TIM6);

    		TIM_SetCounter(TIM6,0);
    		avg = 0;
    		for (uint8_t i = 0; i<=9; i++)
    		{
    			avg += elapsedtime[i];
    		}
    		avg = round(avg/10.);
			sprintf(uartBuffer, "Geschwindigkeit %04.3f s. Average %04.3f s\r\n", (float) 24. * elapsedtime[run_counter]/10000.,(float) 24. * (avg/10000.));
			UART_SendString(uartBuffer);
			run_counter++;
			if (run_counter == 10) { run_counter = 0; }
    	}
    	//elapsedtime =TIM_GetCounter(TIM6);
 //   	elapsedtime = 0;

    }
//    		else {
//
//    	if (TIM_GetCounter(TIM6) > 6)
//    	{
//            // subtract the present counter value (falling edge time) from the rising edge time
//        	elapsedtime = TIM_GetCounter(TIM6);
//        	TIM_SetCounter(TIM6,0);
//        	TIM_Cmd(TIM6,DISABLE);
//
//            // send the measured distance via USART
//            // soundTravellingTime's unit is [10 us]; speed of sound is assumed wo be 340 m/s or 0.34 cm / 10 us
//            // also the ultrasonic chirp traveled double the distance we are interested in
//            sprintf(uartBuffer, "Elapsed time %3i \r\n", (elapsedtime));
//            UART_SendString(uartBuffer);
//            interrupt_count = 15;
//            // prime the uart sending interrupt to send the content of uartTxBuffer
//     //       uart_sendString();
//    	}
}
