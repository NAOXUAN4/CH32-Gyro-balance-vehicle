//
//  pid.h
//  cam_smc_2019
//
//  Created by fukai on 2018/11.
//  Copyright © 2018年 Cyber01. All rights reserved.
//

//
//本文件包括位置式PID（Positional PID）算法和增量式（incremental PID）PID算法
//用户可可再外部函数声明其结构体和调用本头文件函数来使用两种PID
//位置式PID的参数调节方法：先调节KP，待出现抖动再调节KI（KI一般为0.0几），最后调节KD（KD一般很大）
//增量式PID的参数调节方法：先调节KI，再调节KP（步进电机用增量式PID较好）
//注意：kp,ki,kd都必须大于0

#ifndef pid_h
#define pid_h

#include "My_Math.h"

/*
PID结构体初始化说明,以位置式PID为例:
PosiPidNode PosiPid=
{
    .kp = 6.0f,
    .ki = 0.01f,//小车控制中的位置式pid一般只用pd
    .kd = 10.0f,

    .error_curr = 0.0f,
    .error_last = 0.0f,
    .sum_error = 0.0f,

    .limit_out_abs = 1950//限幅，设置为最大pwm即可
};
*/

//
//位置式PID参数结构体
//u(k) = Kp*e(k) + Ki*∑e + Kd*Δe(k) , 式中Δe(k)=e(k)-e(k-1)
typedef struct
{
    float kp;
    float ki;
    float kd;

    float error_curr;   //当前误差
    float error_last;   //上一次的误差
    float sum_error;    //误差和

    float limit_out_abs; //输出限幅
}PosiPidNode;

//
//增量式PID参数结构体
//Δu(k)=u(k)-u(k-1) = Kp*Δe(k)+ Ki*e(k)+ Kd*[Δe(k)-Δe(k-1)] ，式中Δe(k)=e(k)-e(k-1)
typedef struct
{
    float kp;
    float ki;
    float kd;

    float error_curr;   //当前误差（e_0）
    float error_last;   //上一次误差(e_1)
    float error_pre;    //前一次的偏差(e_2)

    float limit_out_abs; //输出限幅
}InrcPidNode;

//位置式PID
void SetPosiPidParm(PosiPidNode *pid, float kp, float ki, float kd);//设置位置式PID参数
float CalcPosiPidOut(PosiPidNode *pid, float expc, float curr);//计算位置式PID输出

//位置式PD
void SetPosiPdParm(PosiPidNode *pid, float kp, float kd);//设置位置式PD参数
float CalcPosiPdOut(PosiPidNode *pid, float expc, float curr);//计算位置式PD输出

//增量式PID
void SetInrcPidParm(InrcPidNode *pid, float kp, float ki, float kd);//设置PID参数
float CalcInrcPidOut(InrcPidNode *pid, float expc, float curr);//计算目标增量

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// int类型信号的pid
typedef struct
{
    float   Target;       // 期望
    float   P;            // 比例系数
    float   I;            // 积分系数
    float   D;            // 微分系数
    float   T_Limit;      // 积分限幅
    float   Limit;        // 计算结果限幅
    float   Error;        // 偏差
    float   LastError;    // 上次的值
    float   DeltError;    // 上次偏差-本次偏差
    float   PrevError;    // 前次偏差
    float   SumError;     // 累计误差
    float   Realize;      // 计算出的差值
} PidNode; 

/*
*  @func PID参数初始化
*  @Author: Wei Zhou
*/
extern void  PID_ParameterInit(PidNode *pid, float P, float I, float D, float Target, float T_Limit, float Limit);
/*
*  @func 位置式PID控制
*  @Author: Wei Zhou
*/
extern float PID_PlaceFloat(PidNode *pid, float target, float now);
/*
*  @func 增量式PID电机控制
*  @Author: Wei Zhou
*/
extern float PID_IncrFloat(PidNode *pid, float target, float now);

#endif


