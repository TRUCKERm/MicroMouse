/*
 * delay.h
 *
 *  Created on: 22.01.2017
 *      Author: Ilja-NP
 */

#ifndef DELAY_H_
#define DELAY_H_
#include "common.h"



void systickInit (uint32_t tickFreq);
void SysTick_Handler (void);
void waitForSysTicks (uint32_t ticks);

#endif /* DELAY_H_ */
