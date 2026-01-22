#ifndef _GPIO_H_
#define _GPIO_H_

#include "stm32f10x.h"
#include <stdio.h>
#include "sys.h"


void MX_GPIO_Init(void);
void MX_Key_Init(void);


#define LED1 PCout(7)   





#endif 


