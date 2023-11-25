#include "ch32v30x.h"
#include "PWM.h"
#include "zf_device_tft180.h"
#include "MONLCD.h"
#include "ENCODER.h"
#include "zf_device_mpu6050.h"
#include "CONTROL.h"




/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{

    PID_init();
    PWM_TIM4_Init(999, 71);
    PWM_TIM8_Init(999, 71);

    MONLCD_init();
    ENCODER_A_init();
    ENCODER_B_init();
    mpu6050_init();

    //事件主时钟开启
    Car_ClockInit();

    while(1)
    {



    }

    //TIM_SetCompare3(TIM4, 40); // r b
    //TIM_SetCompare2(TIM8, 50); // l b


    //TIM_SetCompare2(TIM4, 100);  //r f
    //TIM_SetCompare1(TIM8, 100); // l f

}

