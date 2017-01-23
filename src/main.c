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
#include "analyzer.h"


char uartBuffer[50];
uint32_t elapsedtime = 0;
uint32_t L3GD20_TIMEOUT_UserCallback(void);


int main(void)
{
	Board_init_gpio();
	UART_init();
	UART_enable_interrupt();
    // initiate all Hardware to use the Gyro
    gyroInit();
    lre_ledInit();

	while(1)
	{
		measure_gyro();
	}

}

//void EXTI2_3_IRQHandler(void) {
//
//    // always clear the pending bit
//    EXTI_ClearITPendingBit(EXTI_Line2);
//
//    // because we only us line 11, we don't have to check for other lines generating the interrupt
//    if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)) {
//        // save the present counter value as rising edge time
//  //      soundTravelingTime = TIM_GetCounter(TIM16);
//    	TIM_Cmd(TIM1,ENABLE);
//    	elapsedtime =TIM_GetCounter(TIM1);
//
//    } else {
//        // subtract the present counter value (falling edge time) from the rising edge time
//    	elapsedtime = TIM_GetCounter(TIM1) - elapsedtime;
//    	TIM_Cmd(TIM1,RESET);
//    	TIM_Cmd(TIM1,DISABLE);
//
//        // send the measured distance via USART
//        // soundTravellingTime's unit is [10 us]; speed of sound is assumed wo be 340 m/s or 0.34 cm / 10 us
//        // also the ultrasonic chirp traveled double the distance we are interested in
//        sprintf(uartBuffer, "Elapsed time %5.1d \r\n", (elapsedtime));
//        UART_SendString(uartBuffer);
//        // prime the uart sending interrupt to send the content of uartTxBuffer
// //       uart_sendString();
//    }
//
//}
uint32_t L3GD20_TIMEOUT_UserCallback(void) {
// do nothing
    return 0;
}
