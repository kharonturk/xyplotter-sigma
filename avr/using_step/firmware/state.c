
#include "state.h"
#include "motor.h"
#include "main.h"
#include <avr/io.h>
#include <stdio.h>


static State Idle;
static State Draw;
State* Cur;

static idle_motor_num = 0;

void initialize_state()
{
    initialize_draw();
    initialize_idle();

    Cur = &Idle;
    Cur->initialize();
}

void change_state(enum STATE s)
{
    Cur->clean_up();   
    switch(s)
    {
        case IDLE:
            Cur = &Idle;
            break;
        case DRAW:
            Cur = &Draw;
            break;
        default:
            break;
    }
    Cur->initialize();
}

void initialize_idle()
{
    Idle.initialize = idle_initialize;
    Idle.main_loop = idle_main_loop;
    Idle.process_input = idle_process_input;
    Idle.clean_up = do_nothing;
}

void initialize_draw()
{

    Draw.initialize = draw_initialize;
    Draw.main_loop = do_nothing;
    Draw.process_input = do_not_hear;
    Draw.clean_up = do_nothing;
}

void idle_initialize()
{
    set_stop();
}

void idle_main_loop()
{
    while(stop){
        PORTA=0x00;
        PORTC = 0xff;
    }

    if(dir)
    {
        if(idle_motor_num){
            cycle_forward(100);
        } else {
            cycle_forward2(100);
        }
    }
    else
    {
        if(idle_motor_num){
            cycle_backward(100);
        } else {
            cycle_backward2(100);
        }
    }
    count += 1;
}

void idle_process_input(unsigned char c)
{
    if( c == 'd')
    {
        change_state(DRAW);
    }else if(c == 'f')
    {
        set_dir(1);
        UDR1 = 'f';
        stop = 0;
    }
    else if ( c == 'b')
    {
        set_dir(0);
        UDR1 = 'b';
        stop = 0;
    } else if ( c == 'n')
    {
        idle_motor_num ^= 1;
    } else if ( c == 's')
    {
        set_stop();
        count = 0;
    }
}

void draw_initialize()
{
    printf("Here is draw state!\r\n");
}

void do_nothing(void) {
    _delay_ms(1);
};
void do_not_hear(unsigned char c){};



