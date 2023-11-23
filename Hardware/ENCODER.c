/*
 * ENCODER.c
 *
 *  Created on: Nov 20, 2023
 *      Author: annanyi
 */

#include "ch32v30x.h"

void ENCODER_A_init()
{
    /*************************
     * 初始化：端口，时基单元，中断配置
     ************************/

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitTypeDef GPIO_STU;
    GPIO_STU.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_STU.GPIO_Mode= GPIO_Mode_IN_FLOATING;


    GPIO_STU.GPIO_Pin= GPIO_Pin_11 | GPIO_Pin_9;
    GPIO_Init(GPIOE,&GPIO_STU);



    /*
     * 端口初始化完成
     ********************************/



    /********************************
     * 时基单元
     */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //启用AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);


    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE); // TIM1重映射


    TIM_TimeBaseInitTypeDef TIM_STU1;

    TIM_TimeBaseStructInit(&TIM_STU1);

    TIM_STU1.TIM_ClockDivision=TIM_CKD_DIV1; //预分频
    TIM_STU1.TIM_CounterMode=TIM_CounterMode_Up; //向上递增
    TIM_STU1.TIM_Period= 65535;  //预装载值 （100）ARR
    TIM_STU1.TIM_Prescaler= 0; // (分频)(1KHZ) PSC
    TIM_STU1.TIM_RepetitionCounter = 0; //初始化中断状态


    TIM_TimeBaseInit(TIM1,&TIM_STU1);


    //配置编码器接口的模式、极性、滤波器等参数:
    TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12,
                               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICInitTypeDef IC_InitStructure;
    IC_InitStructure.TIM_ICFilter = 10;
    TIM_ICInit(TIM1, &IC_InitStructure);

    //初始化中断标志位
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);



    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);


    /******************************************
     * TIM_EncoderInterfaceConfig函数:
                配置TIM1工作在编码器接口模式
                设置通道1和通道2的边沿极性
       TIM_ICInit和IC_InitStructure:
                   初始化通道1和通道2作为输入捕获
                    设置输入信号滤波器,过滤抖动
       TIM_ClearFlag:
                    清除更新标志位TIM_FLAG_Update
                    防止一开始就触发中断
       TIM_ITConfig:
                    使能更新中断TIM_IT_Update
                    当计数值更新时会触发中断
     *****************************************/


    TIM_SetCounter(TIM1, 0);

    TIM_Cmd(TIM1, ENABLE);


}


void ENCODER_B_init()
{
    /*************************
     * 初始化：端口，时基单元，中断配置
     ************************/

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_InitTypeDef GPIO_STU;
    GPIO_STU.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_STU.GPIO_Mode= GPIO_Mode_IN_FLOATING;


    GPIO_STU.GPIO_Pin= GPIO_Pin_11 | GPIO_Pin_9;
    GPIO_Init(GPIOD,&GPIO_STU);

    /*
     * 端口初始化完成
     ********************************/



    /********************************
     * 时基单元
     */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //启用AFIO时钟

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM9, ENABLE); // TIM9重映射



    TIM_TimeBaseInitTypeDef TIM_STU1;
    TIM_TimeBaseStructInit(&TIM_STU1);

    TIM_STU1.TIM_ClockDivision=TIM_CKD_DIV1; //预分频
    TIM_STU1.TIM_CounterMode=TIM_CounterMode_Up; //向上递增
    TIM_STU1.TIM_Period= 65535;  //预装载值 （100）ARR
    TIM_STU1.TIM_Prescaler= 0; // (分频)(1KHZ) PSC
    TIM_STU1.TIM_RepetitionCounter = 0; //初始化中断状态

    TIM_TimeBaseInit(TIM9,&TIM_STU1);


    //配置编码器接口的模式、极性、滤波器等参数:
    TIM_EncoderInterfaceConfig(TIM9, TIM_EncoderMode_TI12,
                               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICInitTypeDef IC_InitStructure;
    IC_InitStructure.TIM_ICFilter = 10;
    TIM_ICInit(TIM9, &IC_InitStructure);

    //初始化中断标志位
    TIM_ClearFlag(TIM9, TIM_FLAG_Update);

    TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);


    /******************************************
     * TIM_EncoderInterfaceConfig函数:
                配置TIM1工作在编码器接口模式
                设置通道1和通道2的边沿极性
       TIM_ICInit和IC_InitStructure:
                   初始化通道1和通道2作为输入捕获
                    设置输入信号滤波器,过滤抖动
       TIM_ClearFlag:
                    清除更新标志位TIM_FLAG_Update
                    防止一开始就触发中断
       TIM_ITConfig:
                    使能更新中断TIM_IT_Update
                    当计数值更新时会触发中断
     *****************************************/



    TIM_Cmd(TIM9, ENABLE);

}

/********************************
 *读取速度
 */
int READ_SPEED(int TIMx)
{
    int value = 0;
    switch (TIMx)
    {
        case 9:
            value = (short)TIM_GetCounter(TIM9); TIM_SetCounter(TIM9, 0);
            break;

        case 1:
            value = (short)TIM_GetCounter(TIM1); TIM_SetCounter(TIM1, 0);
            break;
        default:
            break;
    }
    return value;
}

/************************
 * 清除编码器标志位
 */
void TIM1_IRQHandle()
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update)!=0)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }
}

void TIM9_IRQHandle()
{
    if (TIM_GetITStatus(TIM9, TIM_IT_Update)!=0)
    {
        TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
    }
}










