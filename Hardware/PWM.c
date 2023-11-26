/*
 * PWM.c
 *
 *  Created on: Nov 19, 2023
 *      Author: annanyi
 */

#include "ch32v30x.h"
#include "math.h"



/******************
 * PWM波输入控制电机调速:
    B1：C7
    B2：C6
    A1：D13
    A2：D14
 *
 ************************/
void PWM_TIM4_Init(u16 psc,u16 arr)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE); //A
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //启用AFIO时钟
    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);


    GPIO_InitTypeDef GPIO_STU;
    GPIO_StructInit(&GPIO_STU);
    GPIO_STU.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_STU.GPIO_Mode= GPIO_Mode_AF_PP;
    GPIO_STU.GPIO_Pin= GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_Init(GPIOD,&GPIO_STU);



    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //使能TIM4时钟

    TIM_TimeBaseInitTypeDef TIM_STU1;

    TIM_STU1.TIM_ClockDivision=TIM_CKD_DIV1; //预分频
    TIM_STU1.TIM_CounterMode=TIM_CounterMode_Up; //向上递增
    TIM_STU1.TIM_Period= arr;  //预装载值 （100）ARR
    TIM_STU1.TIM_Prescaler= psc; // (分频)(1KHZ) PSC
    TIM_STU1.TIM_RepetitionCounter = 0;

    TIM_TimeBaseInit(TIM4,&TIM_STU1);


    TIM_OCInitTypeDef PWM_STU;
    TIM_OCStructInit(&PWM_STU);
    PWM_STU.TIM_OCMode = TIM_OCMode_PWM1;
    PWM_STU.TIM_OCPolarity = TIM_OCPolarity_High;
    PWM_STU.TIM_OutputState = TIM_OutputState_Enable;
    PWM_STU.TIM_Pulse = 0;  //ccr经过通道比较动态调整


    TIM_OC2Init(TIM4,&PWM_STU);  //D13 A
    TIM_OC3Init(TIM4,&PWM_STU);  //D14

    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_ARRPreloadConfig(TIM4, ENABLE);

    TIM_Cmd(TIM4,ENABLE);

}


void PWM_TIM8_Init(u16 psc,u16 arr)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_TIM8, ENABLE);  //B

    GPIO_InitTypeDef GPIO_STU;
    GPIO_StructInit(&GPIO_STU);
    GPIO_STU.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_STU.GPIO_Mode= GPIO_Mode_AF_PP;


    GPIO_STU.GPIO_Pin= GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Init(GPIOC,&GPIO_STU);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8,ENABLE);

    TIM_TimeBaseInitTypeDef TIM_STU1;

    TIM_STU1.TIM_ClockDivision=TIM_CKD_DIV1; //预分频
    TIM_STU1.TIM_CounterMode=TIM_CounterMode_Up; //向上递增
    TIM_STU1.TIM_Period= arr;  //预装载值 （100）ARR
    TIM_STU1.TIM_Prescaler= psc; // (分频)(1KHZ) PSC
    TIM_STU1.TIM_RepetitionCounter = 0;
    TIM_CtrlPWMOutputs(TIM8,ENABLE);
    TIM_TimeBaseInit(TIM8,&TIM_STU1);


    TIM_OCInitTypeDef PWM_STU;
    TIM_OCStructInit(&PWM_STU);
    PWM_STU.TIM_OCMode = TIM_OCMode_PWM1;
    PWM_STU.TIM_OCPolarity = TIM_OCPolarity_High;
    PWM_STU.TIM_OutputState = TIM_OutputState_Enable;
    PWM_STU.TIM_Pulse = 0;  //ccr经过通道比较动态调整


    TIM_OC1Init(TIM8,&PWM_STU);  //C7 B
    TIM_OC2Init(TIM8,&PWM_STU);  //C6

    TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM8,ENABLE);

    TIM_Cmd(TIM8,ENABLE);
}



void PWM_CRR_TIM4(int32_t compareA)
{
    if (compareA <= 0)
    {
        if(compareA<-100)compareA = -100;
        //if(compareA>-20)compareA = -20;
        TIM_SetCompare3(TIM4,-compareA); //r b
        TIM_SetCompare2(TIM4,0);// l f
    }
    else
    {
        if(compareA>100)compareA = 100;
        //if (compareA<20)compareA = 20;
        TIM_SetCompare3(TIM4, 0);
        TIM_SetCompare2(TIM4,compareA);// l f
    }



}

void PWM_CRR_TIM8(int32_t compareB)
{

    if (compareB <= 0)
        {

        if(compareB<-100)compareB = -100;
        //if (compareB>-20)compareB = 20;
        TIM_SetCompare2(TIM8,-compareB); //l b
        TIM_SetCompare1(TIM8,0);// l f

        }
        else
        {
            if(compareB>100)compareB = 100;
            //if(compareB<20)compareB = 20;
            TIM_SetCompare1(TIM8,compareB);// l f
            TIM_SetCompare2(TIM8,0); //l b
        }


}

