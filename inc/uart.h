/*
 * uart.h
 *
 *  Created on: 21.01.2017
 *      Author: Ilja-NP
 */

#ifndef UART_H_
#define UART_H_



void UART_init();
void UART_enable_interrupt();

void UART_SendString(char *stringPointer);
void UART_sendCrLf(void);

#endif /* UART_H_ */
