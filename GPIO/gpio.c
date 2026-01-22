#include "gpio.h"

void MX_GPIO_Init(void)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		
		GPIO_InitTypeDef GPIO_InitStruct;
		
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOC, &GPIO_InitStruct);
		GPIO_WriteBit(GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9, Bit_SET);
		
	}

	
	void MX_Key_Init(void)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
		GPIO_InitTypeDef GPIO_InitStruct;
		
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		
		GPIO_Init(GPIOA, &GPIO_InitStruct);
	}

	
	
	
	
	