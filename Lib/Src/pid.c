#include "stm32f1xx_hal.h"
#include <math.h>
#include "pid.h"

#include "get_speed.h"
#include "tim.h"

Pid_Data angle_ring = {
    .kp = 0.0f,
    .ki = 0.0f,
    .kd = 0.0f,
    .out_max = 100,
    .out_min = -100
  };

Pid_Data speed_ring_l = {
    .kp = 0.0f,
    .ki = 0.0f,
    .kd = 0.0f,
    .out_max = 100,
    .out_min = -100
  };

Pid_Data speed_ring_r = {
    .kp = 0.0f,
    .ki = 0.0f,
    .kd = 0.0f,
    .out_max = 100,
    .out_min = -100
  };

void PID_update(Pid_Data p) {
    // 计算当前误差
    p.error1 = p.error0;
    p.error0 = p.target - p.actual;
    // 累积误差（积分项）
    if (p.ki != 0.0f) {
        p.errorint += p.error0;
        //积分限幅
        if (p.errorint > (p.out_max / p.ki)) {
            p.errorint = p.out_max / p.ki;
        }
        if (p.errorint < (p.out_min / p.ki)){
            p.errorint = p.out_min / p.ki;
        }
    }
    // PID 输出计算
    p.out = p.kp * p.error0 + p.ki * p.errorint + p.kd * (p.error0 - p.error1);
    // 输出限幅
    if (p.out < p.out_min) {
        p.out = p.out_min;
    }
    if (p.out > p.out_max) {
        p.out = p.out_max;
    }
}





