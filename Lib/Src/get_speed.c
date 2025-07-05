//
// Created by 15350 on 25-7-3.
//
#include "get_speed.h"



int get_speed(TIM_HandleTypeDef *htim)
{
    int temp = (short) __HAL_TIM_GetCounter(htim);   //读取编码器的值，这里一定要用short进行转换，因为我们的计数器是16位的，向下计数，-1对应65535，不进行转换会出错
    __HAL_TIM_SetCounter(htim,0);             //定时器寄存器清零
    int rps = temp / 4;
    return rps;
}
