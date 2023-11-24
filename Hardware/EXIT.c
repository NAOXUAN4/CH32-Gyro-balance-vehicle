/*
 * EXIT.c
 *
 *  Created on: 2023Äê11ÔÂ21ÈÕ
 *      Author: annanyi
 */

#include "ch32v30x.h"

void MPU6050exit_init()
{
    EXTI_InitTypeDef EXTI_MPU;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);

    GPIO_InitTypeDef GPIO_STU;
    GPIO_StructInit(&GPIO_STU);
    GPIO_STU.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_STU.GPIO_Mode= GPIO_Mode_IPU;
    GPIO_STU.GPIO_Pin= GPIO_Pin_5;
    GPIO_Init(GPIOB,&GPIO_STU);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);


    EXTI_MPU.EXTI_Line = EXTI_Line5;
    EXTI_MPU.EXTI_LineCmd = ENABLE;
    EXTI_MPU.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_MPU.EXTI_Trigger = EXTI_Trigger_Rising_Falling;

    EXTI_Init(&EXTI_MPU);



}
