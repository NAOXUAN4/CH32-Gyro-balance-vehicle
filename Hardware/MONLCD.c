/*
 * MONLCD.c
 *
 *  Created on: 2023��11��20��
 *      Author: annanyi
 */

#include "MONLCD.h"
#include "ch32v30x.h"
#include "lcd.h"
#include "lcd_init.h"
#include "ENCODER.h"

void MONLCD_init()
{
    LCD_Init();//LCD��ʼ��
    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);

}




