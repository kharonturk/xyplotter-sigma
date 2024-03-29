
#ifndef _PLOTTER_STATE_H_
#define _PLOTTER_STATE_H_

#include <util/delay.h>

enum STATE
{
    IDLE=0,
    DRAW,
    PICTURE,
};

struct state
{
    void (*initialize)(void);
    void (*main_loop)(void);
    void (*process_input)(unsigned char );
    void (*clean_up)(void);
};

typedef struct state State;

extern State* Cur;

void initialize_state();
void change_state(enum STATE s);
void initialize_idle();
void initialize_draw();
void initialize_picture();


void idle_initialize();
void draw_initialize();
void picture_initialize();

void idle_clean_up();
void draw_clean_up();
void picture_clean_up();

void idle_main_loop();
void draw_main_loop();
void picture_main_loop();

void idle_process_input(unsigned char);
void draw_process_input(unsigned char);
void picture_process_input(unsigned char);

void do_nothing();
void do_not_hear(unsigned char);

void get_data(int* buf);

#endif

