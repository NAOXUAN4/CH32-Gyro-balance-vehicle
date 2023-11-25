/*
 * CONTROL.c
 *
 *  Created on: 2023��11��22��
 *      Author: annanyi
 */

#include "sys.h"
#include "pid.h"
#include "ENCODER.h"
#include "zf_device_mpu6050.h"
#include "MONLCD.h"

PosiPidNode vRing;
PosiPidNode sRing;

float vRingConfig[3] = {10,3,0}; // kp ki
float sRingConfig[3] = {10,0,1};  //kp kd
float Mid = 2.5;
float v_expect = 0;

int ENCO_A = 0, ENCO_B = 0;
float ANgle = 0;

float vRing_Out = 0;
int PID_Out = 0;

void PID_init()
{
    SetPosiPdParm(&sRing, sRingConfig[0], sRingConfig[2]);
    SetPosiPidParm(&vRing, vRingConfig[0], vRingConfig[1], vRingConfig[2]);
}

/*********************
 * ��Ļ����
 */

void MON_Control(void)
{
    MONLCD_ENCO(ENCO_A,ENCO_B);
    MONLCD_MPU(ANgle);
}

/******************
 * ֱ����
 */
int PID_sRing(float Angle, float Mid, float vRing_Out)
{
    int PWM_OUT;

    sRing.limit_out_abs=100;

    PWM_OUT = CalcPosiPdOut(&sRing, Mid, Angle+vRing_Out);

    return PWM_OUT;
}

/******************
 * �ٶȻ�
 */
float PID_vRing(int ECO_A, int ECO_B, int v_ecpect)
{
    float vRing_OUT = 0.0;

    vRing.limit_out_abs = 90;

    float v_AVE =  ECO_A;  //(ECO_A + ECO_B)/2;


    vRing_OUT = CalcInrcPidOut(&vRing,v_ecpect,v_AVE);

    return vRing_OUT;
}


void Car_ClockInit()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    /*
    //��AFIO��ѡ��·������Ϊ�ж�ģʽ
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
    */

    TIM_TimeBaseInitTypeDef timerInitStructure;

    // ʹ�ܶ�ʱ��ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 1000000/72000000 - 1;
    timerInitStructure.TIM_Prescaler = 72 - 1;
    timerInitStructure.TIM_RepetitionCounter = 0;

    // ��ʼ����ʱ������
    TIM_TimeBaseInit(TIM3, &timerInitStructure);

    // ʹ�ܶ�ʱ���ж�
    TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef TIM3_NVIC;
    TIM3_NVIC.NVIC_IRQChannel = TIM3_IRQn;
    TIM3_NVIC.NVIC_IRQChannelCmd = ENABLE;
    TIM3_NVIC.NVIC_IRQChannelPreemptionPriority = 0;
    TIM3_NVIC.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&TIM3_NVIC);

    // ʹ�ܶ�ʱ��
    TIM_Cmd(TIM3, ENABLE);
}



void TIM3_IRQHandler()
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update))
    {
        if (1)
        {
            //PWM_CRR_TIM4(40);
            //PWM_CRR_TIM8(40);

            TIM_ClearITPendingBit(TIM3, TIM_IT_Update);


            ENCO_A = READ_SPEED(1);
            ENCO_B = READ_SPEED(9);

            Get_Angle();
            ANgle = mpu.angle;

            MON_Control();



            vRing_Out = PID_vRing(ENCO_A, ENCO_B, v_expect);

            PID_Out = PID_sRing(ANgle, Mid, vRing_Out);

            MOTOR_DC_A_SPEED(PID_Out);
            MOTOR_DC_B_SPEED(PID_Out);


        }

    }
}




