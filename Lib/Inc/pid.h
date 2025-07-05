/*
 * pid.h
 *
 *  Created on: Jun 25, 2025
 *      Author: 15350
 */

#ifndef INC_PID_H_
#define INC_PID_H_

typedef struct
{
    float target;
    float actual;
    float out;

    float kp;
    float ki;
    float kd;

    float error0;
    float error1;
    float errorint;

    float out_max;
    float out_min;
} Pid_Data;

extern  Pid_Data angle_ring;
extern  Pid_Data speed_ring_l;
extern  Pid_Data speed_ring_r;

void PID_update(Pid_Data p);

#endif // INC_PID_H_
