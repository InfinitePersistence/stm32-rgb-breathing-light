
#include "time.h"
#include "gpio.h"


void MX_TIM3_Init(uint16_t Period,uint16_t Prescaler,uint8_t Preemption, uint8_t Sub)
{
//------------------1.TIM3 时钟使能------------------------
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

//------------------2.TIM3 Init----------------------------
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

  TIM_TimeBaseInitStruct.TIM_Period 						= Period;							//自动重装载值
  TIM_TimeBaseInitStruct.TIM_Prescaler 					= Prescaler;					//预分频值
  TIM_TimeBaseInitStruct.TIM_ClockDivision 			= TIM_CKD_DIV1;				//时钟缩水倍数
  TIM_TimeBaseInitStruct.TIM_CounterMode			 	= TIM_CounterMode_Up;	//向上计数
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter 	= 0;									//每隔N次更新产生一次中断
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
//------------------3.TIM IT Config(在什么时候产生中断)----------------------------
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//配置TIM更新中断
	
//------------------4.NVIC Init----------------------------
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel										= TIM3_IRQn;		//选择中断0通道
	NVIC_InitStruct.NVIC_IRQChannelCmd								= ENABLE;				//使能中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = Preemption;		//抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority				= Sub;					//响应优先级

	NVIC_Init(&NVIC_InitStruct);
	
//------------------5.TIM3 启动----------------------------
	TIM_Cmd(TIM3, ENABLE);
	
	
	
}


void TIM3_IRQHandler(void)
{	
		//1.判断是否产生更新中断
	if( TIM_GetITStatus( TIM3,TIM_IT_Update) == SET)
	{
		//2.处理中断任务
		LED1 = !LED1;
	}
		//3.清除更新中断
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
}












