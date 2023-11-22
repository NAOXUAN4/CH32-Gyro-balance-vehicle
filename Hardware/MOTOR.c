/*
 * MOTOR.c
 *
 *  Created on: Nov 19, 2023
 *      Author: annanyi
 */

#include "ch32v30x.h"
#include "PWM.h"

void MOTOR_Init(u16 arr,u16 psc)
{
    PWM_TIM4_Init(psc, arr);
    PWM_TIM8_Init(psc, arr);

}

void MOTOR_DC_A_SPEED(int8_t MOTOR_SPEED)
{

    PWM_CRR_TIM4(MOTOR_SPEED);

}
void MOTOR_DC_B_SPEED(int8_t MOTOR_SPEED)
{
    PWM_CRR_TIM8(MOTOR_SPEED);

}
void MOTOR_EXIT()
{
    TIM_SetCompare1(TIM8,0);

    TIM_SetCompare2(TIM8,0);

    TIM_SetCompare2(TIM4,0);

    TIM_SetCompare3(TIM4,0);

}

