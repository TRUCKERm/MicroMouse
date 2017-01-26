/*
 * common.h
 *
 *  Created on: 21.01.2017
 *      Author: Ilja-NP
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "stm32f0xx.h"
#include "stm32f0xx_rcc.h"
#include "stm32f0xx_adc.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_flash.h"
#include "stm32f0xx_adc.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_flash.h"
#include "stm32f0xx_syscfg.h"
#include "stm32f0xx_pwr.h"
#include "stm32f0xx_rtc.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_dac.h"
#include "stm32f072b_discovery.h"
#include "string.h"
//#include "stm32f0xx_conf.h"
#include "stdio.h"
#include "math.h"

extern uint8_t datenErhalt;
extern uint8_t drehRateMessen;
extern uint8_t Aread, Bready;
extern uint8_t gyroMessen;
extern uint8_t gyro_ready;

#endif /* COMMON_H_ */
