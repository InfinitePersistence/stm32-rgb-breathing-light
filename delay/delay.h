#ifndef _DELAY_H_
#define _DELAY_H_


#include "stm32f10x.h"
#include <stdio.h>

#define fac_us ((SystemCoreClock/8)/1000000)
#define fac_ms ((SystemCoreClock/8)/1000)

void delay_Init(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
#endif

