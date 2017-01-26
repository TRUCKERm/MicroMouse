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
#include "lre_gyro.h"
#include "ultraschall.h"


char uartBuffer[50];
uint32_t elapsedtime = 0;
uint32_t L3GD20_TIMEOUT_UserCallback(void);
uint8_t datenErhalt = 0;
uint8_t drehRateMessen=0;
uint8_t Aready = 0, Bready = 0;
uint8_t gyroMessen = 0;
uint8_t gyro_ready = 0;

int main(void)
{
	systickInit(1000);
	datenErhalt=0;
	gyroInit();
	Board_init_gpio();
	Board_enable_timers();
	UART_init();
	UART_enable_interrupt();
    waitForSysTicks(500);
    init_ultrasonicSensor_intputPin_Left();
    init_ultrasonicSensor_outputPin_Left();
    init_ultrasonicSensor_timer_Left();
    waitForSysTicks(500);
    init_ultrasonicSensor_intputPin_Front();
    init_ultrasonicSensor_outputPin_Front();
    init_ultrasonicSensor_timer_Front();
    waitForSysTicks(500);
    init_ultrasonicSensor_intputPin_Right();
    init_ultrasonicSensor_outputPin_Right();
    init_ultrasonicSensor_timer_Right();
    // initiate all Hardware to use the Gyro;
    waitForSysTicks(500);
    lre_ledInit();
    uint8_t i = 0;
	uint8_t j = 0;//	TIM_SetCompare1(TIM17, 1000);
//	TIM_SetCompare1(TIM16, 2000);

	while(1)
	{
		measure_gyro();
		if (datenErhalt==1){

			UART_analyzer();
		}

		if (drehRateMessen)
		{
			if (Aready && Bready)
			{
				drehRateAusgeben();
				i++;
				if (i > 10)
				{
					drehRateMessen = 0;
					i = 0;
					TIM_Cmd(TIM6,DISABLE);
					TIM_Cmd(TIM7,DISABLE);
					TIM_SetCounter(TIM6,0);
					TIM_SetCounter(TIM7,0);
				}
			}
		}

	if (gyroMessen)
	{
			//if (gyro_ready) {
			gyroAusgeben();
			j++;
			if (j>49){
			gyroMessen=0;
			//}
		}


	}

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
