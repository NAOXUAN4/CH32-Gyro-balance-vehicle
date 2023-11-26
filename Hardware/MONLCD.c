/*
 * MONLCD.c
 *
 *  Created on: 2023Äê11ÔÂ20ÈÕ
 *      Author: annanyi
 */

#include "MONLCD.h"
#include "ch32v30x.h"
#include "zf_device_tft180.h"



void MONLCD_init(void)
{
    tft180_set_dir(TFT180_CROSSWISE_180);
    tft180_init();

    tft180_full(RGB565_GREEN);

    tft180_set_color(RGB565_BLUE, RGB565_WHITE);
    tft180_show_string(5,5, "EHOP10DFFUTJ60");
    tft180_show_string(5,5, "HELLO WORLD :)");

    tft180_show_string(5,25, "MPU>>ANGLE:");

    tft180_show_string(5,45, "ENCODERA>>V_A:");
    tft180_show_string(5,65, "ENCODERB>>V_B:");

    tft180_show_string(5,85, "vR:");
    tft180_show_string(95,85, "sR:");



}

void MONLCD_ENCO(int ENCO_A,int ENCO_B)
{


   tft180_set_color(RGB565_BLUE, RGB565_WHITE);
   tft180_show_int(120, 45, ENCO_A, 2);
   tft180_show_int(120, 65, ENCO_B, 2);

}

void MONLCD_MPU(float ANgle)
{

    tft180_set_color(RGB565_BLUE, RGB565_WHITE);
    tft180_show_float(95, 25, ANgle, 4, 1);

}

void MONLCD_RING(float vRINGOUT,int sRINGOUT)
{
    tft180_set_color(RGB565_BLUE, RGB565_WHITE);
    tft180_show_float(45, 85, vRINGOUT, 4, 1);
    tft180_show_int(120, 85, sRINGOUT, 3);
}




