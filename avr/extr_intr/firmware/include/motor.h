
#ifndef __MOTOR_PLOTTER_H_
#define __MOTOR_PLOTTER_H_

typedef struct motor
{
    unsigned char dir;
    int speed; // 1 is slowest 254 is fastest
} Motor;

extern volatile Motor motorA;

void motor_init();
void timer_init();

#endif
