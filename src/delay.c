/*
 * delay.c
 *
 *  Created on: 22.01.2017
 *      Author: Ilja-NP
 */
#include "delay.h"


volatile uint32_t timerTicks;

void systickInit (uint32_t tickFreq)
{
  /* Check the parameters */
  assert_param((SystemCoreClock / tickFreq) <= (1 << 24));

  /* activate SysTick Timer */
  SysTick_Config (SystemCoreClock / tickFreq);
}

void SysTick_Handler (void)
{
  // count only down to 0
  if (timerTicks != 0)
    {
      timerTicks--;
    }
}

/**
 * @brief waits until the number of ticks has passed.
 * @param ticks: number of ticks the controller will wait
 */
void waitForSysTicks (uint32_t ticks)
{
  timerTicks = ticks;

  // wait until the SysTick interrupt handler has decreased to 0
  while (timerTicks != 0)
    {
      // do nothing
    }
}
