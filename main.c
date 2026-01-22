/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "delay.h"
#include "gpio.h"
#include "exti.h"
#include "usart.h"
#include "time.h"
#include "pwm.h"

#define TIM3CH1_ARR 20000-1
#define TIM3CH2_ARR 20000-1
#define TIM3CH3_ARR 20000-1



uint8_t SendData[] = {"System Init OK! \r\n"};

int main(void)
{
	
//	uint16_t Compare1 = 0;
//	uint16_t Compare2 = 0;
//	uint16_t Compare3 = 0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	MX_GPIO_Init();
	delay_Init();
	MX_EXTI0_Init( 2, 2 );
	MX_USART1_Init(115200);
	MX_USART1_NVIC_Init( 1, 1 );
	MX_TIM3_PWM_Init(TIM3CH1_ARR,72-1);

	uint16_t MAX = TIM3CH1_ARR;   // ARR = 20000-1
	uint16_t STEP = 1;          // 呼吸步进

	uint16_t r = 0, g = 0, b = 0; // 亮度值：0..MAX
	int8_t phase = -1;            // -1:红单独上升; 0:RG接力; 1:GB接力; 2:BR接力



	while (1)
{
    // 
    if (phase == -1) {
        // 红单独渐亮到顶
        if (r + STEP >= MAX) { r = MAX; phase = 0; }
        else r += STEP;
        g = 0; b = 0;
    }
    else if (phase == 0) {
        // R 渐灭，同时 G 渐亮
        if (r <= STEP) { r = 0; phase = 1; }
        else r -= STEP;

        if (g + STEP >= MAX) g = MAX;
        else g += STEP;

        b = 0;
    }
    else if (phase == 1) {
        // G 渐灭，同时 B 渐亮
        if (g <= STEP) { g = 0; phase = 2; }
        else g -= STEP;

        if (b + STEP >= MAX) b = MAX;
        else b += STEP;

        r = 0;
    }	
    else { // phase == 2
        // B 渐灭，同时 R 渐亮
        if (b <= STEP) { b = 0; phase = 0; }
        else b -= STEP;

        if (r + STEP >= MAX) r = MAX;
        else r += STEP;

        g = 0;
    }
		
		    // ===== 低电平亮：反相写 CCR =====
    // PC6=TIM3_CH1=B, PC7=TIM3_CH2=G, PC8=TIM3_CH3=R 
    TIM_SetCompare1(TIM3, MAX - b);   // CH1 -> B
    TIM_SetCompare2(TIM3, MAX - g);   // CH2 -> G
    TIM_SetCompare3(TIM3, MAX - r);   // CH3 -> R

    delay_us(100);
		
		
}

}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/


