#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void MX_USART1_Init(uint32_t BaudRate);
void MX_USART1_NVIC_Init(uint8_t preemption, uint8_t sub);


#define U1RX_MAX_LEN 128


extern char 		U1Rx_DATA[ U1RX_MAX_LEN ] ;  		//数据接收区
extern uint8_t U1RX_LEN ;												//数据接收长度
extern bool  	U1RX_IDLE_FLAG ;




#endif 

