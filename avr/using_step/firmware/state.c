
#include "state.h"
#include "motor.h"
#include "main.h"
#include "draw.h"
#include "uart.h"
#include <avr/io.h>
#include <stdio.h>

static volatile unsigned char data[16];
static volatile unsigned char size = 0;
static volatile unsigned char data_received;

static volatile char ServerReady;
static State Idle;
static State Draw;
static State Picture;
State* Cur;

static idle_motor_num = 0;

void initialize_state()
{
    initialize_draw();
    initialize_idle();
    initialize_picture();


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
        case PICTURE:
            Cur = &Picture;
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
    Idle.clean_up = idle_clean_up;
}

void initialize_draw()
{

    Draw.initialize = draw_initialize;
    Draw.main_loop = draw_main_loop;
    Draw.process_input = draw_process_input;
    Draw.clean_up = draw_clean_up;
}

void initialize_picture()
{
    Picture.initialize = picture_initialize;
    Picture.main_loop = picture_main_loop;
    Picture.process_input = picture_process_input;
    Picture.clean_up = picture_clean_up;
}

void picture_initialize()
{
    //uart rx interrupt disable;
    set_stop();
//    uart_rx_intr_disable();
    point_initialize(&Pen, 0,0);
    point_initialize(&Obj, 0,0);
    ServerReady = 0;
    data_received = 0;
//    printf("Picture mode Start!");
}

void picture_main_loop()
{
    char buffer[16];
    int arr[3];

    while ( ServerReady == 0);

    while(1)
    {
        printf("d\n");
//        scanf("%d %d %d",&arr[0], &arr[1], &arr[2]);
        
        get_data(arr);
    //    printf("%d %d %d\n",arr[0], arr[1], arr[2]);
        if ( arr[2] == -1) break;
        point_initialize(&Obj, arr[0], arr[1]);
        draw();
    }

    change_state(IDLE);

}

void picture_clean_up()
{
//    uart_rx_intr_enable();
}
void get_data(int * buf)
{
    while(1) 
        if ( data_received == 1) break;;

    data_received = 0;
    if ( 3 > sscanf(data, "%d %d %d", &buf[0], &buf[1], &buf[2]))
    {
        printf("%d\n");
        return get_data(buf);   
    };

    return;
}

void picture_process_input(unsigned char c)
{
    static unsigned char start = 0;

    if ( ServerReady == 0)
    {
        if ( c != 'r')
        {
            return;
        }
        ServerReady = 1;
    }
    if ( start == 0)
    {
        if ( c != 'S')
        {
            return;
        }
        start = 1;
    }

    else
    {
        if ( c == 'E')
        {
            data[size] = 0;
            start = 0;
            size = 0;
            data_received = 1;
            return;
        }
        data[size++] = c;   
    }
}

void idle_initialize()
{
    set_stop();
}

void idle_main_loop()
{
    if(stop) return;

    if(dir)
    {
        if(idle_motor_num){
            cycle_forward(10);
        } else {
            cycle_forward2(10);
        }
    }
    else
    {
        if(idle_motor_num){
            cycle_backward(10);
        } else {
            cycle_backward2(10);
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
    } else if ( c == 'p')
    {
        set_stop();
        change_state(PICTURE);
    }
}

void idle_clean_up(){
    set_stop();
}

void draw_initialize()
{
    set_stop();
    //printf("Here is draw state!\r\n");
    stop = 0;
//    cycle_forward(1000);
    //cycle_forward2(1000);
    point_initialize(&Pen, 0,0);
    point_initialize(&Obj, 0,0);
}

void draw_main_loop()
{

    while(!stop)
    {
        draw_circle();
        draw_triangle(500);
        draw_rectangle(200);
    }

}

void draw_process_input(unsigned char c )
{
    if( c == 'i')
    {
        change_state(IDLE);
    } else if ( c == 's')
    {
        set_stop();
    }

}
void draw_clean_up()
{
    set_stop();
}

void do_nothing(void) {
    _delay_ms(1);
};
void do_not_hear(unsigned char c){};



