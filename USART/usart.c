#include "usart.h"

char 		U1Rx_DATA[ U1RX_MAX_LEN ] = {0};  	//数据接收区
uint8_t U1RX_LEN = 0;												//数据接收长度
bool  	U1RX_IDLE_FLAG = 0;


void MX_USART1_Init( uint32_t BaudRate )
{
//--------------------------- 1、GPIO Init ----------------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //打开IO口的管脚复用时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//PA9  TX
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_AF_PP;    //复用推挽输出
	GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_9; 				//该参数选择待设置的 GPIO 管脚，使用操作符“|”可以一次选中多个管脚
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;   //最高输出速率 50MHz
  GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//PA10  RX
	GPIO_InitStruct.GPIO_Mode 	= GPIO_Mode_IPU;      //上拉输入
	GPIO_InitStruct.GPIO_Pin 		= GPIO_Pin_10; 				//该参数选择待设置的 GPIO 管脚，使用操作符“|”可以一次选中多个管脚
	GPIO_InitStruct.GPIO_Speed 	= GPIO_Speed_50MHz;   //最高输出速率 50MHz
  GPIO_Init(GPIOA, &GPIO_InitStruct);
	
//--------------------------- 2、USART Init ----------------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
	USART_InitTypeDef USART_InitStruct;
	
	USART_InitStruct.USART_BaudRate 						= BaudRate;  //波特率
	USART_InitStruct.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None; //不使用硬件流控制
	USART_InitStruct.USART_Mode 								= USART_Mode_Rx | USART_Mode_Tx;  //串口收发工作模式
	USART_InitStruct.USART_Parity 							= USART_Parity_No; //不校验
	USART_InitStruct.USART_StopBits 						= USART_StopBits_1;  //1 位停止位
	USART_InitStruct.USART_WordLength 					= USART_WordLength_8b;  //8位数据位
	
	USART_Init(USART1, &USART_InitStruct);
	
//--------------------------- 3、USART Cmd ----------------------------
	USART_Cmd( USART1, ENABLE );  //串口使能
	
}

void MX_USART1_NVIC_Init( uint8_t Preemption, uint8_t Sub )
{
//--------------------------- 1、USART IT Config ----------------------
	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE);   //使能串口接收中断
	USART_ITConfig( USART1, USART_IT_IDLE, ENABLE);   //使能串口空闲中断
	
//--------------------------- 2、NVIC Init ----------------------------
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_InitStruct.NVIC_IRQChannel 									= USART1_IRQn; //选择中断串口1中断
	NVIC_InitStruct.NVIC_IRQChannelCmd 								= ENABLE;      //使能中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = Preemption;  //抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority 				= Sub;				 //响应优先级
	
	NVIC_Init(&NVIC_InitStruct);
}


//--------------------------- 串口中断函数 ----------------------------
void USART1_IRQHandler(void)
{
	if( USART_GetITStatus( USART1, USART_IT_RXNE) == SET )
	{
		if(U1RX_LEN < U1RX_MAX_LEN)
			U1Rx_DATA[ U1RX_LEN++ ] = USART_ReceiveData(USART1);
		else
			U1RX_IDLE_FLAG = 1; //如果超过接收区最大接收长度则强制设置接收标志位为1，进行数据处理
	}
	if( USART_GetITStatus( USART1, USART_IT_IDLE) == SET )
	{
		//软件序列清除该位(先读USART_SR，然后读USART_DR)
		USART1->SR;
		USART1->DR;
		
		U1RX_IDLE_FLAG = 1;  //数据已经接收完成
	}
}




//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ x = x; } 

//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
    while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
   return ch;
}
#endif 



