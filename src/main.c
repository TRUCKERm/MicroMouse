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
uint32_t elapsedtime2[10];
uint32_t run_counter2 = 0;
uint16_t interrupt_count2 = 0;
uint16_t avg2 = 0;
uint8_t temp1 = 0, temp2 = 0;
uint8_t Aready = 0, Bready = 0;

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

		TIM_SetCompare1(TIM17, 1500);
		TIM_SetCompare1(TIM16, 2000);
		TIM_Cmd(TIM6,ENABLE);
		TIM_Cmd(TIM7,ENABLE);
		if (Aready && Bready)
		{
			sprintf(uartBuffer, "Geschwindigkeit Rechts %04.3f cm/s. Links %04.3f cm/s\r\n", (float) 17.3 / (48. * avg/10000.),(float) 17.3 / (48. * (avg2/10000.)));
			UART_SendString(uartBuffer);
			Aready = 0;
			Bready = 0;
		}

#define TEMP110_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7C2))
#define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7B8))
#define VDD_CALIB ((uint16_t) (330))
#define VDD_APPLI ((uint16_t) (300))
		ADC1->CHSELR = ADC_CHSELR_CHSEL16; /* (1) */
		ADC1->SMPR |= ADC_SMPR_SMP_0 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_2; /* (2) */
		ADC->CCR |= ADC_CCR_TSEN; /* (3) */
int32_t temperature; /* will contain the temperature in degree Celsius */
temperature = (((int32_t) ADC1->DR * VDD_APPLI / VDD_CALIB)
- (int32_t) *TEMP30_CAL_ADDR );
temperature = temperature * (int32_t)(110 - 30);
temperature = temperature / (int32_t)(*TEMP110_CAL_ADDR - *TEMP30_CAL_ADDR);
temperature = temperature + 30;

	}
}

void EXTI4_15_IRQHandler(void){
	   // always clear the pending bit
	    EXTI_ClearITPendingBit(EXTI_Line12);

	    // because we only us line 11, we don't have to check for other lines generating the interrupt
	    if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_12)) {
	        // save the present counter value as rising edge time
	  //      soundTravelingTime = TIM_GetCounter(TIM16);
	  //  	TIM_Cmd(TIM6,ENABLE);
	    	interrupt_count2++;
//	    	if (temp2 == 0)
//	    	{
//	    		temp2 = TIM_GetCounter(TIM7);
//	    		if ((temp2 <= 0) || (temp2>=4000))
//	    		{
//	    			temp2 = 0;
//	    		}
//	    	}
//	    	else if (temp2 != 0)
//	    	{
				if ((interrupt_count2 >= 1) && (TIM_GetCounter(TIM7) > 80))
				{
//					elapsedtime2[run_counter2] = TIM_GetCounter(TIM7) - temp2;
					elapsedtime2[run_counter2] = TIM_GetCounter(TIM7) ;
					TIM_SetCounter(TIM7,0);
//					temp2 = 0;
					avg2 = 0;

					for (uint8_t i = 0; i<=9; i++)
					{
						avg2 += elapsedtime2[i];
					}

					avg2 = round(avg2/10.);
					Bready = 1;
					run_counter2++;
					if (run_counter2 == 10) { run_counter2 = 0; }
				}
//	    	}
	    	//elapsedtime =TIM_GetCounter(TIM6);
	 //   	elapsedtime = 0;

	    }
}

void EXTI2_3_IRQHandler(void) {

    // always clear the pending bit
    EXTI_ClearITPendingBit(EXTI_Line2);

	    // because we only us line 11, we don't have to check for other lines generating the interrupt
	    if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)) {
	        // save the present counter value as rising edge time
	  //      soundTravelingTime = TIM_GetCounter(TIM16);
	  //  	TIM_Cmd(TIM6,ENABLE);
	    	interrupt_count++;
//	    	if (temp1 == 0)
//	    	{
//	    		temp1 = TIM_GetCounter(TIM6);
//	    		if ((temp1 <= 0) || (temp1>=4000))
//	    		{
//	    			temp1 = 0;
//	    		}
//	    	}
//	    	else if (temp1 != 0)
//	    	{
				if ((interrupt_count >= 1) && (TIM_GetCounter(TIM6) > 80))
				{
//					elapsedtime[run_counter] = TIM_GetCounter(TIM6) - temp1;
					elapsedtime[run_counter] = TIM_GetCounter(TIM6);
					TIM_SetCounter(TIM6,0);
//					temp1 = 0;
					avg = 0;

					for (uint8_t i = 0; i<=9; i++)
					{
						avg += elapsedtime[i];
					}
					Aready = 1;
					avg = round(avg/10.);
					run_counter++;
					if (run_counter == 10) { run_counter = 0; }
				}
//	    	}
	    	//elapsedtime =TIM_GetCounter(TIM6);
	 //   	elapsedtime = 0;

	    }
}
