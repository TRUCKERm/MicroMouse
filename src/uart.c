/*
 * uart.c
 *
 *  Created on: 21.01.2017
 *      Author: Ilja-NP
 */

#include "uart.h"
#include "common.h"
#include "analyzer.h"

char uartRxBuffer[30]; // this is the receiving buffer.
uint16_t zaehler = 550;
uint8_t charCounter = 0; // this variable counts the characters in uartRxBuffer (8-bit unsigned)

void UART_init()
{
    //---- initiate the usart module ----
    // 115200 baud, 8N1 (8 data bits, no parity check, 1 stop bit)
    // USART1 is located at the APB2 Bus of the microcontroller
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    USART_InitTypeDef uartInitStruct;
    uartInitStruct.USART_BaudRate = 115200; // Baudrates can go up to 6MBaud. Table 96 in the reference manual gives an overview on default baudrates
    uartInitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // no flow control necessary. The three other modes are using the cts (clear to send) and rts (request to send) pins
    uartInitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // here you can choose if you just need the receiver, transmitter or both. This is the only setting where you should "or" the options
    uartInitStruct.USART_Parity = USART_Parity_No; // no Parity check. Other settings define a parity bit. It shows if the number of ones in the data byte is even or odd (see de.wikipedia.org/wiki/Paritätsbit)
    uartInitStruct.USART_StopBits = USART_StopBits_1; // just one stop bit. other options would use 1.5 or 2 stop bits.
    uartInitStruct.USART_WordLength = USART_WordLength_8b; // this defines the length of the data between in one transmission. The STM32F072 supports 7, 8 or 9 data bits. 8 data bits is the usual setting

    // initiate USART1 with the settings written in our struct
    USART_Init(USART1, &uartInitStruct);
    // usart modules also have to be enabled before they work
    USART_Cmd(USART1, ENABLE);
}

void UART_enable_interrupt()
{
	 // Tell USART1 that it shall request an interrupt when the Receiver is Not Empty (RXNE)
	    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // ctrl + left click on USART_ITConfig to see a full list of the 13 possible interrupt events of the USART Modules
	    // The Nested Vector Interrupt Controller needs to be enabled too.
	    // Otherwise the NVIC would just ignore any interrupt requests from USART1
	    NVIC_EnableIRQ(USART1_IRQn); // The STM32F07s NVIC supports 32 so called interrupt vectors (Interrupt Handlers). ctrl + left click on USART1_IRQn to see the full list
}

void UART_SendString(char *stringPointer)
{
	if (*stringPointer != '\0')
	{
		while (*stringPointer != '\0') {
			// wait for transmit register to be empty
			while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE)) {
			}
			// send character
			USART_SendData(USART1, *stringPointer);
			// increase the address to which the stringPointer is pointing
			stringPointer++;
		}
//		UART_sendCrLf();
	}
}

void UART_sendCrLf(void)
{
	//send carriage return and line feed
	while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE)) {
	}
	USART_SendData(USART1, '\r');
	while (!USART_GetFlagStatus(USART1, USART_FLAG_TXE)) {
	}
	USART_SendData(USART1, '\n');
}

void USART1_IRQHandler() {
    USART_ClearITPendingBit(USART1, USART_IT_RXNE); // we don't have to check which event triggered the interrupt because we only activated the rxne interrupt
    // now save the received char
    uartRxBuffer[charCounter] = USART_ReceiveData(USART1);
    // check for the termination characters '\r' and '\n'
    if (uartRxBuffer[charCounter] == '\n') {
        // we now have to check if there are already more than one character in the buffer. Remember: charCounter starts counting at zero
        if (charCounter >= 1) {
            // now check for the carriage return \r
            if (uartRxBuffer[charCounter - 1] == '\r')
            {
                // Removes \n and \r from the string
                uartRxBuffer[charCounter - 1] = '\0';
                UART_SendString("got it\0");
                UART_sendCrLf();
                UART_SendString(uartRxBuffer);
                UART_sendCrLf();
                uartInterrupt(uartRxBuffer);



                charCounter = -1;
            }
        }
    }
    // uartInterrupt(uartRxBuffer);
//    UART_SendString(uartRxBuffer);
    // increase counter by one
    charCounter++;
}
