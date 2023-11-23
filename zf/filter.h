#ifndef __FILTER_H
#define __FILTER_H
#include "zf_common_headfile.h"
extern float angle, angle_dot;


uint8  filter_flag_check(void);
void Kalman_Filter(float Accel,float Gyro);

#endif
