/*
 * PWM.h
 *
 *  Created on: Nov 19, 2023
 *      Author: annanyi
 */

#ifndef HARDWARE_PWM_H_
#define HARDWARE_PWM_H_


void PWM_TIM8_Init(u16 arr,u16 psc);
void PWM_TIM4_Init(u16 arr,u16 psc);
void PWM_CRR_TIM4(int32_t compareA);
void PWM_CRR_TIM8(int32_t compareB);


#endif /* HARDWARE_PWM_H_ */
