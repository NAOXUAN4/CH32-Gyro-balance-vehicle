/*
 * CONTROL.h
 *
 *  Created on: 2023Äê11ÔÂ22ÈÕ
 *      Author: annanyi
 */

#ifndef __CONTROL__
#define __CONTROL__


void PID_init(void);
void TIM3_IRQHandler(void);
int PID_sRing(float Angle, float Mid, float vRing_Out);
float vRing(int ECO_A, int ECO_B, int v_ecpect);
void MON_Control(void);







#endif
