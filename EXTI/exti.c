#include "exti.h"

void MX_EXTI0_Init(uint32_t Preemption,uint32_t Sub)
{
//--------------------1.GPIO 初始化--------------------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	
	
	
//--------------------2.EXTI 初始化--------------------------------
	EXTI_InitTypeDef EXTI_InitStruct;
	
  EXTI_InitStruct.EXTI_Line		 = EXTI_Line0;						//中断线0
  EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;		//采用中断模式
  EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;	//采用下降沿触发方式
  EXTI_InitStruct.EXTI_LineCmd = ENABLE;								//使能中断线
	
	EXTI_Init(&EXTI_InitStruct);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); //
//--------------------3.NVIC(中断优先级) 初始化-----------------------
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel										= EXTI0_IRQn;	//选择中断0通道
	NVIC_InitStruct.NVIC_IRQChannelCmd								= ENABLE;			//使能中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = Preemption;	//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority				= Sub;					//响应优先级

	NVIC_Init(&NVIC_InitStruct);
}
	

BitAction BEEP_BitVal = Bit_SET;

void EXTI0_IRQHandler(void)
{
	if( GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == Bit_RESET)
	{
		BEEP_BitVal = (BitAction) !BEEP_BitVal;
	
		GPIO_WriteBit( GPIOC,GPIO_Pin_9,BEEP_BitVal);
	}
	EXTI_ClearITPendingBit(EXTI_Line0);//清除中断线





}








