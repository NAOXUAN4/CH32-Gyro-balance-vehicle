//
//  pid.c
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

#include "pid.h"


/**********位置式PID部分**********/
//u(k) = Kp*e(k) + Ki*∑e + Kd*Δe(k) , 式中Δe(k)=e(k)-e(k-1)
//设置位置式PID参数
void SetPosiPidParm(PosiPidNode *pid, float kp, float ki, float kd)
{
    //限制范围
    if(kp < 0)
    {
        kp = 0;
    }
    if(ki < 0)
    {
        ki = 0;
    }
    if(kd < 0)
    {
        kd = 0;
    }
    pid ->kp = kp;
    pid ->ki = ki;
    pid ->kd = kd;
}

//计算位置式PID输出
//输入参数
//expc:期望值
//curr:当前值
float CalcPosiPidOut(PosiPidNode *pid, float expc, float curr)
{
	
    float ep=0, ei=0, ed=0;
    float posi_out=0;
	
	
    pid ->error_curr = expc - curr;
    pid ->sum_error += pid ->error_curr;

    ep = pid ->error_curr ;
    ei = pid ->sum_error;
    ed = pid ->error_curr - pid ->error_last;

    posi_out = pid->kp * ep + pid->ki * ei + pid->kd * ed;
	
	
	
    if(posi_out > pid ->limit_out_abs)
    {
        posi_out = pid ->limit_out_abs;
    }
    else if(posi_out < - pid ->limit_out_abs)
    {
        posi_out = - (pid ->limit_out_abs);
		posi_out = - (100.0);
    }

    pid ->error_last = pid ->error_curr;
	
    return posi_out;
}


/**********位置式PD部分**********/
//u(k) = Kp*e(k) + Kd*Δe(k) , 式中Δe(k)=e(k)-e(k-1)
//设置位置式PD参数
void SetPosiPdParm(PosiPidNode *pid, float kp, float kd)
{
    //限制范围
    if(kp < 0)
    {
        kp = 0;
    }
    if(kd < 0)
    {
        kd = 0;
    }
    pid ->kp = kp;
    pid ->kd = kd;
}

//计算位置式PD输出
float CalcPosiPdOut(PosiPidNode *pid, float expc, float curr) //期望，实际
{
    float ep=0, ed=0;
    float posi_out=0;
    
    pid ->error_curr = expc - curr;

    ep = pid ->error_curr ;
    ed = pid ->error_curr - pid ->error_last;

    posi_out = pid->kp * ep + pid->kd * ed;
	
	
	
    if(posi_out > pid ->limit_out_abs)
    {
        posi_out = pid ->limit_out_abs;
    }
    else if(posi_out < - pid ->limit_out_abs)
    {
        posi_out = - pid ->limit_out_abs;
    }

    pid ->error_last = pid ->error_curr;

    return posi_out;
}


/**********增量式PID部分**********/
//Δu(k)=u(k)-u(k-1) = Kp*Δe(k)+ Ki*e(k)+ Kd*[Δe(k)-Δe(k-1)] ，式中Δe(k)=e(k)-e(k-1)

//设置增量式PID参数
void SetInrcPidParm(InrcPidNode *pid, float kp, float ki, float kd)
{
    //限制范围
    if(kp < 0)
    {
        kp = 0;
    }
    if(ki < 0)
    {
        ki = 0;
    }
    if(kd < 0)
    {
        kd = 0;
    }
    pid ->kp = kp;
    pid ->ki = ki;
    pid ->kd = kd;
}

//计算增量式PID目标增量
//输入参数
//expc:期望值
//curr:当前值
float CalcInrcPidOut(InrcPidNode *pid, float expc, float curr)
{
    float ep=0, ei=0, ed=0;
    float inrc_out=0;
    
    pid ->error_curr = expc - curr;

    ep = pid->error_curr - pid->error_last;
    ei = pid->error_curr;
    ed = pid->error_curr - 2*pid->error_last + pid->error_pre;
    
    inrc_out = pid->kp * ep + pid->ki * ei + pid->kd * ed;
    if(inrc_out > pid ->limit_out_abs)
    {
        inrc_out = pid ->limit_out_abs;
    }
    else if(inrc_out < - pid ->limit_out_abs)
    {
        inrc_out = - pid ->limit_out_abs;
    }

    pid->error_pre = pid->error_last;
    pid->error_last = pid->error_curr;

    return inrc_out;
}


/**********增量式PID部分**********/
/*
*  @func PID参数初始化
*  @Author: Wei Zhou
*/
void PID_ParameterInit(PidNode *pid, float P, float I, float D, float Target, float T_Limit, float Limit)
{
    pid->P = P;
    pid->I = I;
    pid->D = D;
    pid->Target = Target;
    pid->T_Limit = T_Limit;
    pid->Limit = Limit;
  
    pid->LastError = 0;
    pid->PrevError = 0;
    pid->SumError  = 0;
}

/*
*  @func 位置式PID控制
*  @Author: Wei Zhou
*/
float PID_PlaceFloat(PidNode *pid, float target, float now)
{
    pid->Error = target - now; // 计算当前误差
    pid->SumError =  pid->Error + pid->LastError + pid->PrevError; // 误差积分
    pid->SumError = _limit(pid->SumError, -pid->T_Limit, pid->T_Limit);

    pid->DeltError  = pid->Error - pid->LastError; //微分项
    
    pid->Realize = (pid->P * pid->Error
                  + pid->I * pid->SumError
                  + pid->D * pid->DeltError);

    pid->PrevError = pid->LastError;// 更新前次误差
    pid->LastError = pid->Error;    // 更新上次误差
    
    pid->Realize = _limit(pid->Realize, -pid->Limit, pid->Limit);
    return pid->Realize; // 返回实际值
}

/*
*  @func 增量式PID电机控制
*  @Author: Wei Zhou
*/
float PID_IncrFloat(PidNode *pid, float target, float now)
{
    pid->Error = target - now;   // 计算当前误差
    pid->Realize  = (pid->P * (pid->Error - pid->LastError)
                  + pid->I * pid->Error
                  + pid->D * (pid->Error - 2 * pid->LastError + pid->PrevError));

    pid->PrevError = pid->LastError;// 更新前次误差
    pid->LastError = pid->Error;    // 更新上次误差
    
    pid->Realize = _limit(pid->Realize, -pid->Limit, pid->Limit);
    return pid->Realize; // 返回增量
}






