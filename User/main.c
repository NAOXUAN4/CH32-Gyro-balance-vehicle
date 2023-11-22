#include "ch32v30x.h"
#include "PWM.h"
#include "lcd.h"
#include "lcd_init.h"


//#include "lcd_init.h"
//#include "lcd.h"
//#include "pic.h"

/* Global typedef */

/* Global define */

/* Global Variable */


/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    LCD_Init();
    PWM_TIM4_Init(999, 71);
    PWM_TIM8_Init(999, 71);

    //PWM_CRR_TIM4(-100);


    //TIM_SetCompare3(TIM4, 0); // r b
    //TIM_SetCompare2(TIM8, 0); // l b
    //TIM_SetCompare2(TIM4, 100);  //r f
    //TIM_SetCompare1(TIM8, 100); // l f


    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);
        while(1)
        {
            LCD_ShowChinese(0,0,"ÄãºÃ£¬ÊÀ½ç",RED,WHITE,24,0);
            LCD_ShowString(24,30,"LCD_W:",RED,WHITE,16,0);
            LCD_ShowIntNum(72,30,LCD_W,3,RED,WHITE,16);
            LCD_ShowString(24,50,"LCD_H:",RED,WHITE,16,0);
            LCD_ShowIntNum(72,50,LCD_H,3,RED,WHITE,16);
        }
}

