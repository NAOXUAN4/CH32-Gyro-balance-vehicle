/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
*
* �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file             zf_device_mpu6050
* @company          �ɶ���ɿƼ����޹�˾
* @author           ��ɿƼ�(QQ790875685)
* @version          �鿴doc��version�ļ� �汾˵��
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
* @note             ���߶��壺
*                   ------------------------------------
*                   ģ��ܽ�                                        ��Ƭ���ܽ�
*                   ���� IIC ͨ�����Ŷ�Ӧ��ϵ
*                   SCL                 �鿴 zf_device_mpu6050.h �� MPU6050_SOFT_IIC_SCL �궨��
*                   SDA                 �鿴 zf_device_mpu6050.h �� MPU6050_SOFT_IIC_SDA �궨��
*                   Ӳ�� IIC ͨ�����Ŷ�Ӧ��ϵ
*                   SCL                 �鿴 zf_device_mpu6050.h �� MPU6050_IIC_SCL �궨��
*                   SDA                 �鿴 zf_device_mpu6050.h �� MPU6050_IIC_SDA �궨��
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
// @brief       MPU6050 �Լ� �ڲ�����
// @param       void
// @return      uint8         1-�Լ�ʧ�� 0-�Լ�ɹ�
//-------------------------------------------------------------------------------------------------------------------
static uint8 mpu6050_self1_check(void)
{
    uint8 dat = 0;
    volatile int16 timeout_count = MPU6050_TIMEOUT_COUNT;

    mpu6050_write_register(PWR_MGMT_1, 0x00);                                   // �������״̬
    mpu6050_write_register(SMPLRT_DIV, 0x07);                                   // 125HZ������
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
// @brief       ��ʼ�� MPU6050
// @param       void
// @return      uint8         1-��ʼ��ʧ�� 0-��ʼ���ɹ�
// Sample usage:
//-------------------------------------------------------------------------------------------------------------------
uint8 mpu6050_init (void)
{

    soft_iic_init(&mpu6050_iic_struct, MPU6050_DEV_ADDR, MPU6050_SOFT_IIC_DELAY, MPU6050_SCL_PIN, MPU6050_SDA_PIN);

    system_delay_ms(100);                                                       // �ϵ���ʱ

    if(mpu6050_self1_check())
    {
        zf_log(0, "MPU6050 self check error.");
        return 1;
    }
    mpu6050_write_register(PWR_MGMT_1, 0x00);                                   // �������״̬
    mpu6050_write_register(SMPLRT_DIV, 4);                                      // 200HZ������ 1k/(N+1)


    //mpu6050_write_register(MPU6050_CONFIG, 0x06);

    mpu6050_write_register(GYRO_CONFIG, 0x18);                                  // 2000
    mpu6050_write_register(ACCEL_CONFIG, 0x00);                                 //���ٶȶ�������� +-2G

    mpu6050_write_register(USER_CONTROL, 0x00);
    mpu6050_write_register(INT_PIN_CFG, 0x02);
    return 0;
}


//��������ֲ�Ľ��㲿�ִ���=========================================================================================================================================================

void Get_Angle(void)
{
    float Accel_Y,Accel_X,Accel_Z,Gyro_X,Gyro_Y,Gyro_Z;
    Gyro_X=(mpu6050_read_register(GYRO_XOUT_H)<<8)+mpu6050_read_register(GYRO_XOUT_L);    //��ȡX��������
    Gyro_Y=(mpu6050_read_register(GYRO_YOUT_H)<<8)+mpu6050_read_register(GYRO_YOUT_L);    //��ȡY��������
    Gyro_Z=(mpu6050_read_register(GYRO_ZOUT_H)<<8)+mpu6050_read_register(GYRO_ZOUT_L);    //��ȡY��������
    Accel_Y=(mpu6050_read_register(ACCEL_YOUT_H)<<8)+mpu6050_read_register(ACCEL_YOUT_L);    //��ȡZ��������
    Accel_X=(mpu6050_read_register(ACCEL_XOUT_H)<<8)+mpu6050_read_register(ACCEL_XOUT_L); //��ȡX����ٶȼ�
    Accel_Z=(mpu6050_read_register(ACCEL_ZOUT_H)<<8)+mpu6050_read_register(ACCEL_ZOUT_L); //��ȡZ����ٶȼ�
    if(Gyro_Y>32768)  Gyro_Y-=65536;                       //��������ת��  Ҳ��ͨ��shortǿ������ת��
    if(Gyro_Z>32768)  Gyro_Z-=65536;                       //��������ת��
    if(Gyro_X>32768)  Gyro_X-=65536;                       //��������ת��
    if(Accel_X>32768) Accel_X-=65536;                      //��������ת��
    if(Accel_Z>32768) Accel_Z-=65536;                      //��������ת��
    if(Accel_Y>32768) Accel_Y-=65536;                      //��������ת��

    Accel_Y=atan2(Accel_X,Accel_Z)*180/PI;                 //�������
    mpu.acc_y=Accel_Y;

    Gyro_X=Gyro_X/16.4;                                         //����������ת��
    mpu.gyro_x=Gyro_X;
    Gyro_Y=Gyro_Y/16.4;                                         //����������ת��
    mpu.gyro_y=Gyro_Y;
    Gyro_Z=Gyro_Z/16.4;                                         //����������ת��
    mpu.gyro_Z=Gyro_Z;

    Kalman_Filter(Accel_Y,-Gyro_Y);//�������˲�


    mpu.angle = angle;                                       //����ƽ�����


}



