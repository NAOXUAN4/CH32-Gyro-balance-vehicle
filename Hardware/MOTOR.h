/*
 * MOTOR.h
 *
 *  Created on: Nov 19, 2023
 *      Author: annanyi
 */

#ifndef HARDWARE_MOTOR_H_
#define HARDWARE_MOTOR_H_

void MOTOR_Init(u16 pri,u16 psc);
void MOTOR_DC_A_SPEED(int8_t MOTOR_SPEED);
void MOTOR_DC_B_SPEED(int8_t MOTOR_SPEED);



#endif /* HARDWARE_MOTOR_H_ */
