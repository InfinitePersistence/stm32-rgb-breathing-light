#include "pwm.h"

void MX_TIM3_PWM_Init(uint16_t Period,uint16_t Prescaler)
{
//-------------------1.AFIO Init-------------------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //使能AFIO管脚复用时钟
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);			//使能TIM3的完全重映射
//-------------------2.GPIO Init-------------------------------
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		
		GPIO_InitTypeDef GPIO_InitStruct;
		
		GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;				//复用推挽输出
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			
		GPIO_Init(GPIOC, &GPIO_InitStruct);

//-------------------3.TIM3 Init-------------------------------
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

  TIM_TimeBaseInitStruct.TIM_Period 						= Period;							//自动重装载值   就是 ARR
  TIM_TimeBaseInitStruct.TIM_Prescaler 					= Prescaler;					//预分频值       就是 PSC
  TIM_TimeBaseInitStruct.TIM_ClockDivision 			= TIM_CKD_DIV1;				//时钟缩水倍数
  TIM_TimeBaseInitStruct.TIM_CounterMode			 	= TIM_CounterMode_Up;	//向上计数
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter 	= 0;									//每隔N次更新产生一次中断
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct); //把上面这些“写进 TIM3 的寄存器”（CR1/PSC/ARR 等）



//-------------------4.OCx Init--------------------------------
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_OCStructInit(&TIM_OCInitStruct);   // 先把结构体填默认值（强烈推荐）
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;							//采用PWM1模式
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;			//输出极性为高
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;	//使能输出极性
	TIM_OCInitStruct.TIM_Pulse= 0;        // 初始占空比

	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);
	TIM_OC3Init(TIM3,&TIM_OCInitStruct);

	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);						//使能 TIMx 在CCR3 上的预装载寄存器
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);						//使能 TIMx 在CCR3 上的预装载寄存器
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);						//使能 TIMx 在CCR2 上的预装载寄存器
	TIM_ARRPreloadConfig(TIM3, ENABLE);													//使能 TIMx 在ARR 上的预装载寄存器

//-------------------5.TIM3 启动--------------------------------
	TIM_Cmd(TIM3, ENABLE);
 
}

