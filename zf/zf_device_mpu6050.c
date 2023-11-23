/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             zf_device_mpu6050
* @company          成都逐飞科技有限公司
* @author           逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
* @note             接线定义：
*                   ------------------------------------
*                   模块管脚                                        单片机管脚
*                   软件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_mpu6050.h 中 MPU6050_SOFT_IIC_SCL 宏定义
*                   SDA                 查看 zf_device_mpu6050.h 中 MPU6050_SOFT_IIC_SDA 宏定义
*                   硬件 IIC 通信引脚对应关系
*                   SCL                 查看 zf_device_mpu6050.h 中 MPU6050_IIC_SCL 宏定义
*                   SDA                 查看 zf_device_mpu6050.h 中 MPU6050_IIC_SDA 宏定义
*                   ------------------------------------
********************************************************************************************************************/

#include "zf_device_mpu6050.h"
#include <math.h>

static soft_iic_info_struct mpu6050_iic_struct;
#define mpu6050_write_register(reg,data)       soft_iic_write_8bit_register(&mpu6050_iic_struct,reg,data)
#define mpu6050_read_register(reg)             soft_iic_read_8bit_register(&mpu6050_iic_struct,reg)
#define mpu6050_read_registers(reg,data,len)   soft_iic_read_8bit_registers(&mpu6050_iic_struct,reg,data,len)

#define PI 3.14159265
MpuNode mpu;

//-------------------------------------------------------------------------------------------------------------------
// @brief       MPU6050 自检 内部调用
// @param       void
// @return      uint8         1-自检失败 0-自检成功
//-------------------------------------------------------------------------------------------------------------------
static uint8 mpu6050_self1_check(void)
{
    uint8 dat = 0;
    volatile int16 timeout_count = MPU6050_TIMEOUT_COUNT;

    mpu6050_write_register(PWR_MGMT_1, 0x00);                                   // 解除休眠状态
    mpu6050_write_register(SMPLRT_DIV, 0x07);                                   // 125HZ采样率
    while(0x07 != dat && timeout_count)
    {
        timeout_count--;
        dat = mpu6050_read_register(SMPLRT_DIV);
        system_delay_ms(10);
    }

    if(timeout_count < 0)
        return 1;
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       初始化 MPU6050
// @param       void
// @return      uint8         1-初始化失败 0-初始化成功
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 mpu6050_init (void)
{

    soft_iic_init(&mpu6050_iic_struct, MPU6050_DEV_ADDR, MPU6050_SOFT_IIC_DELAY, MPU6050_SCL_PIN, MPU6050_SDA_PIN);

    system_delay_ms(100);                                                       // 上电延时

    if(mpu6050_self1_check())
    {
        zf_log(0, "MPU6050 self check error.");
        return 1;
    }
    mpu6050_write_register(PWR_MGMT_1, 0x00);                                   // 解除休眠状态
    mpu6050_write_register(SMPLRT_DIV, 4);                                      // 200HZ采样率 1k/(N+1)


    //mpu6050_write_register(MPU6050_CONFIG, 0x06);

    mpu6050_write_register(GYRO_CONFIG, 0x18);                                  // 2000
    mpu6050_write_register(ACCEL_CONFIG, 0x00);                                 //加速度度最大量程 +-2G

    mpu6050_write_register(USER_CONTROL, 0x00);
    mpu6050_write_register(INT_PIN_CFG, 0x02);
    return 0;
}


//下面是移植的解算部分代码=========================================================================================================================================================

void Get_Angle(void)
{
    float Accel_Y,Accel_X,Accel_Z,Gyro_X,Gyro_Y,Gyro_Z;
    Gyro_X=(mpu6050_read_register(GYRO_XOUT_H)<<8)+mpu6050_read_register(GYRO_XOUT_L);    //读取X轴陀螺仪
    Gyro_Y=(mpu6050_read_register(GYRO_YOUT_H)<<8)+mpu6050_read_register(GYRO_YOUT_L);    //读取Y轴陀螺仪
    Gyro_Z=(mpu6050_read_register(GYRO_ZOUT_H)<<8)+mpu6050_read_register(GYRO_ZOUT_L);    //读取Y轴陀螺仪
    Accel_Y=(mpu6050_read_register(ACCEL_YOUT_H)<<8)+mpu6050_read_register(ACCEL_YOUT_L);    //读取Z轴陀螺仪
    Accel_X=(mpu6050_read_register(ACCEL_XOUT_H)<<8)+mpu6050_read_register(ACCEL_XOUT_L); //读取X轴加速度计
    Accel_Z=(mpu6050_read_register(ACCEL_ZOUT_H)<<8)+mpu6050_read_register(ACCEL_ZOUT_L); //读取Z轴加速度计
    if(Gyro_Y>32768)  Gyro_Y-=65536;                       //数据类型转换  也可通过short强制类型转换
    if(Gyro_Z>32768)  Gyro_Z-=65536;                       //数据类型转换
    if(Gyro_X>32768)  Gyro_X-=65536;                       //数据类型转换
    if(Accel_X>32768) Accel_X-=65536;                      //数据类型转换
    if(Accel_Z>32768) Accel_Z-=65536;                      //数据类型转换
    if(Accel_Y>32768) Accel_Y-=65536;                      //数据类型转换

    Accel_Y=atan2(Accel_X,Accel_Z)*180/PI;                 //计算倾角
    mpu.acc_y=Accel_Y;

    Gyro_X=Gyro_X/16.4;                                         //陀螺仪量程转换
    mpu.gyro_x=Gyro_X;
    Gyro_Y=Gyro_Y/16.4;                                         //陀螺仪量程转换
    mpu.gyro_y=Gyro_Y;
    Gyro_Z=Gyro_Z/16.4;                                         //陀螺仪量程转换
    mpu.gyro_Z=Gyro_Z;

    Kalman_Filter(Accel_Y,-Gyro_Y);//卡尔曼滤波


    mpu.angle = angle;                                       //更新平衡倾角


}



