#ifndef _PLOTTER_MOTOR_H_
#define _PLOTTER_MOTOR_H_

#define B (1<<6)
#define G (1<<4)
#define R (1<<2)
#define D (1<<0)

extern volatile unsigned int dir;
extern volatile unsigned int stop;

void cycle_forward(int cycle);
void cycle_backward(int cycle);
void cycle_forward2(int cycle);
void cycle_backward2(int cycle);
void set_dir(int i);

void set_stop();


#endif
