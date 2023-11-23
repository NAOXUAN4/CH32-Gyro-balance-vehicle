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
     * ��ʼ�����˿ڣ�ʱ����Ԫ���ж�����
     ************************/

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
    GPIO_InitTypeDef GPIO_STU;
    GPIO_STU.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_STU.GPIO_Mode= GPIO_Mode_IN_FLOATING;


    GPIO_STU.GPIO_Pin= GPIO_Pin_11 | GPIO_Pin_9;
    GPIO_Init(GPIOE,&GPIO_STU);



    /*
     * �˿ڳ�ʼ�����
     ********************************/



    /********************************
     * ʱ����Ԫ
     */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //����AFIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);


    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE); // TIM1��ӳ��


    TIM_TimeBaseInitTypeDef TIM_STU1;

    TIM_TimeBaseStructInit(&TIM_STU1);

    TIM_STU1.TIM_ClockDivision=TIM_CKD_DIV1; //Ԥ��Ƶ
    TIM_STU1.TIM_CounterMode=TIM_CounterMode_Up; //���ϵ���
    TIM_STU1.TIM_Period= 65535;  //Ԥװ��ֵ ��100��ARR
    TIM_STU1.TIM_Prescaler= 0; // (��Ƶ)(1KHZ) PSC
    TIM_STU1.TIM_RepetitionCounter = 0; //��ʼ���ж�״̬


    TIM_TimeBaseInit(TIM1,&TIM_STU1);


    //���ñ������ӿڵ�ģʽ�����ԡ��˲����Ȳ���:
    TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12,
                               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICInitTypeDef IC_InitStructure;
    IC_InitStructure.TIM_ICFilter = 10;
    TIM_ICInit(TIM1, &IC_InitStructure);

    //��ʼ���жϱ�־λ
    TIM_ClearFlag(TIM1, TIM_FLAG_Update);



    TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);


    /******************************************
     * TIM_EncoderInterfaceConfig����:
                ����TIM1�����ڱ������ӿ�ģʽ
                ����ͨ��1��ͨ��2�ı��ؼ���
       TIM_ICInit��IC_InitStructure:
                   ��ʼ��ͨ��1��ͨ��2��Ϊ���벶��
                    ���������ź��˲���,���˶���
       TIM_ClearFlag:
                    ������±�־λTIM_FLAG_Update
                    ��ֹһ��ʼ�ʹ����ж�
       TIM_ITConfig:
                    ʹ�ܸ����ж�TIM_IT_Update
                    ������ֵ����ʱ�ᴥ���ж�
     *****************************************/


    TIM_SetCounter(TIM1, 0);

    TIM_Cmd(TIM1, ENABLE);


}


void ENCODER_B_init()
{
    /*************************
     * ��ʼ�����˿ڣ�ʱ����Ԫ���ж�����
     ************************/

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_InitTypeDef GPIO_STU;
    GPIO_STU.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_STU.GPIO_Mode= GPIO_Mode_IN_FLOATING;


    GPIO_STU.GPIO_Pin= GPIO_Pin_11 | GPIO_Pin_9;
    GPIO_Init(GPIOD,&GPIO_STU);

    /*
     * �˿ڳ�ʼ�����
     ********************************/



    /********************************
     * ʱ����Ԫ
     */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //����AFIOʱ��

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM9, ENABLE); // TIM9��ӳ��



    TIM_TimeBaseInitTypeDef TIM_STU1;
    TIM_TimeBaseStructInit(&TIM_STU1);

    TIM_STU1.TIM_ClockDivision=TIM_CKD_DIV1; //Ԥ��Ƶ
    TIM_STU1.TIM_CounterMode=TIM_CounterMode_Up; //���ϵ���
    TIM_STU1.TIM_Period= 65535;  //Ԥװ��ֵ ��100��ARR
    TIM_STU1.TIM_Prescaler= 0; // (��Ƶ)(1KHZ) PSC
    TIM_STU1.TIM_RepetitionCounter = 0; //��ʼ���ж�״̬

    TIM_TimeBaseInit(TIM9,&TIM_STU1);


    //���ñ������ӿڵ�ģʽ�����ԡ��˲����Ȳ���:
    TIM_EncoderInterfaceConfig(TIM9, TIM_EncoderMode_TI12,
                               TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
    TIM_ICInitTypeDef IC_InitStructure;
    IC_InitStructure.TIM_ICFilter = 10;
    TIM_ICInit(TIM9, &IC_InitStructure);

    //��ʼ���жϱ�־λ
    TIM_ClearFlag(TIM9, TIM_FLAG_Update);

    TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);


    /******************************************
     * TIM_EncoderInterfaceConfig����:
                ����TIM1�����ڱ������ӿ�ģʽ
                ����ͨ��1��ͨ��2�ı��ؼ���
       TIM_ICInit��IC_InitStructure:
                   ��ʼ��ͨ��1��ͨ��2��Ϊ���벶��
                    ���������ź��˲���,���˶���
       TIM_ClearFlag:
                    ������±�־λTIM_FLAG_Update
                    ��ֹһ��ʼ�ʹ����ж�
       TIM_ITConfig:
                    ʹ�ܸ����ж�TIM_IT_Update
                    ������ֵ����ʱ�ᴥ���ж�
     *****************************************/



    TIM_Cmd(TIM9, ENABLE);

}

/********************************
 *��ȡ�ٶ�
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
 * �����������־λ
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










