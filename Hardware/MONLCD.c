/*
 * MONLCD.c
 *
 *  Created on: 2023年11月20日
 *      Author: annanyi
 */

#include "MONLCD.h"
#include "ch32v30x.h"
#include "lcd.h"
#include "lcd_init.h"
#include "ENCODER.h"

void MONLCD_init()
{
    LCD_Init();//LCD初始化
    LCD_Fill(0,0,LCD_W,LCD_H,WHITE);

}




