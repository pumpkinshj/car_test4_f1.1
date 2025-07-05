

#include "motor.h"
#include "tim.h"

//右电机速度
void Set_Pwmr(int out)
{
    int pwmb_abs;// 存储PWM绝对值
    pwmb_abs=myabs(out);
    // 根据输入值正负设置电机方向
    if(out>=0) Motor_Right(1);// 正转
    else      Motor_Right(0);// 反转
    //设置速度
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,pwmb_abs);
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_4,pwmb_abs);
}
//左电机速度
void Set_Pwml(int out)//赋值给PWM寄存器
{
    int pwma_abs;
    pwma_abs=myabs(out);
    if(out>=0) Motor_Left(1);
    else      Motor_Left(0);
    //设置速度
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,pwma_abs);
    __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,pwma_abs);
}

void Motor_Right(int a)
{
    if(a == 1){
        HAL_GPIO_WritePin(R_IN2_GPIO_Port,R_IN2_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(R_IN1_GPIO_Port,R_IN1_Pin,GPIO_PIN_SET);//即01，正转
    }
    else if(a == 0){
        HAL_GPIO_WritePin(R_IN2_GPIO_Port,R_IN2_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(R_IN1_GPIO_Port,R_IN1_Pin,GPIO_PIN_RESET);//即01，反转
    }
}

void Motor_Left(int a)
{
    if(a == 1){
        HAL_GPIO_WritePin(L_IN2_GPIO_Port,L_IN2_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(L_IN1_GPIO_Port,L_IN1_Pin,GPIO_PIN_SET);//即01，正转
    }
    else if(a == 0){
        HAL_GPIO_WritePin(L_IN2_GPIO_Port,L_IN2_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(L_IN1_GPIO_Port,L_IN1_Pin,GPIO_PIN_RESET);//即01，反转
    }
}

/*
*    函数功能：取绝对值
*    入口参数：int
*    返回值：无 unsingned int
*/
int myabs(int num)
{
    int temp;
    if(num<0)    temp=-num;
    else temp =num;
    return temp;
}