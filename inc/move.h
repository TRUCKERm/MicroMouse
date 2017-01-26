/*
 * Move.h
 *
 *  Created on: 21.01.2017
 *      Author: Ilja-NP
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "analyzer.h"
#include "common.h"
#include "uart.h"
#include "servo.h"
#include "delay.h"


void move_speed(int speed);
void move_distance(int dist);
void move_stop(void);
void servo_pwm(int pwm_left, int pwm_right);

#endif /* MOVE_H_ */
