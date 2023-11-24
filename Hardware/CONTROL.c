/*
 * CONTROL.c
 *
 *  Created on: 2023年11月22日
 *      Author: annanyi
 */

#include "sys.h"
#include "pid.h"
#include "ENCODER.h"
#include "zf_device_mpu6050.h"
#include "MONLCD.h"

PosiPidNode vRing;
PosiPidNode sRing;

float vRingConfig[3] = {1,1,0}; // kp ki
float sRingConfig[3] = {1,0,1};  //kp kd
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
 * 屏幕控制
 */

void MON_Control(void)
{
    MONLCD_ENCO(ENCO_A,ENCO_B);
    MONLCD_MPU(ANgle);
}




/******************
 * 直立环
 */
int PID_sRing(float Angle, float Mid, float vRing_Out)
{
    int PWM_OUT;

    sRing.limit_out_abs=100;

    PWM_OUT = CalcPosiPdOut(&sRing, Mid, Angle+vRing_Out);

    return PWM_OUT;
}

/******************
 * 速度环
 */
float PID_vRing(int ECO_A, int ECO_B, int v_ecpect)
{
    float vRing_OUT = 0.0;

    vRing.limit_out_abs = 90;

    float v_AVE =  ECO_A;  //(ECO_A + ECO_B)/2;


    vRing_OUT = CalcInrcPidOut(&vRing,v_ecpect,v_AVE);

    return vRing_OUT;
}

void EXIT_9_5IRQHandler()
{
    if (EXTI_GetITStatus(EXTI_Line5))
    {
        if (!PBin(5))
        {
            EXTI_ClearFlag(EXTI_Line5);
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




