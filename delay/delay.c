#include "delay.h"

//------------------初始化systick的时钟----------------------
void delay_Init(void)
{
	
SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//SysTick选择 AHB 8分频 = 72/8 = 9MHz
	
}//-----------------2.systick的延时函数-----------------------


void delay_us(uint32_t us)//us最大1864135
{
	uint32_t temp = 0;
	
	SysTick->LOAD = fac_us * us;									//load赋初值	
	SysTick->VAL = 0;                             //清空Val寄存器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     //启动SysTick
	do
	{
	 temp = SysTick -> CTRL;
	}
	while((temp & 0x01) && (!(temp & (0x01<<16))));		//判断systick是否启动并且死等到0
  SysTick ->CTRL &= !SysTick_CTRL_ENABLE_Msk;		//关闭Systick
	SysTick->VAL = 0;
}

void delay_ms(uint32_t ms)//us最大1864
{
	uint32_t temp = 0;
	
	SysTick->LOAD = fac_ms * ms;									//load赋初值	
	SysTick->VAL = 0;                             //清空Val寄存器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;     //启动SysTick
	do
	{
	 temp = SysTick -> CTRL;
	}
	while((temp & 0x01) && (!(temp & (0x01<<16))));		//判断systick是否启动并且死等到0
  SysTick ->CTRL &= !SysTick_CTRL_ENABLE_Msk;		//关闭Systick
	SysTick->VAL = 0;
}
