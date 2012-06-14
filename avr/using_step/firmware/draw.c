
#include "motor.h"
#include "draw.h"
#include <stdio.h>

#define abs(x) ( (x>0)? (x):(-x))

volatile Point Pen;
volatile Point Obj;

void draw()
{
    Point diff;
    if ( (Pen.x == Obj.x)
            && (Pen.y == Obj.y))
        return;

    diff.x = Obj.x - Pen.x;
    diff.x = abs(diff.x);
    diff.y = Obj.y - Pen.y;
    diff.y = abs(diff.y);


    if ( diff.x >= diff.y)
    {
        lineBres_less_1(Pen.x, Pen.y, Obj.x, Obj.y);
        Pen.x = Obj.x; Pen.y = Obj.y;
    }

    else
    {
        lineBres_more_1(Pen.y, Pen.x, Obj.y, Obj.x);
        Pen.x = Obj.x; Pen.y = Obj.y;
    }

}

void lineBres_more_1(int x0, int y0, int xEnd, int yEnd) // reverse x, y
{

    int dx = xEnd - x0, dy = yEnd-y0;
    dx = abs(dx); dy = abs(dy);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy, twoDyMinusDx = 2 * ( dy - dx );
    int x, y;
    int x_dir = 0, y_dir=0;

    if ( x0 > xEnd ) {
        x = xEnd;
        xEnd = x0;
        x_dir = 0;
    }

    else {
        x = x0;
        x_dir = 1;
    }

    if ( y0 > yEnd)
    {
        y_dir = 0;       
    }

    else {

        y_dir = 1;
    }

    // assert now is x0, y0

    while( x < xEnd )
    {
        x++;
        if (x_dir)
            cycle_forward2(1);
        else
            cycle_backward2(1);

        if ( p < 0 ){
            p += twoDy;
        }
        else {
            y++;
            if (y_dir)
                cycle_forward(1);
            else
                cycle_backward(1);
            p += twoDyMinusDx;
        }
    }
}

void lineBres_less_1(int x0, int y0, int xEnd, int yEnd)
{
    int dx = xEnd - x0, dy = yEnd-y0;
    dx = abs(dx); dy = abs(dy);
    int p = 2 * dy - dx;
    int twoDy = 2 * dy, twoDyMinusDx = 2 * ( dy - dx );
    int x, y=0;
    int x_dir = 0, y_dir = 0;

    if ( x0 > xEnd ) {
        x = xEnd;
        xEnd = x0;
        x_dir = 0;
    }

    else {
        x = x0;
        x_dir = 1;
    }

    if ( y0 > yEnd)
    {
        y_dir = 0;
    }
    else  // y < yEnd
    {
        y_dir = 1;
    }

    printf("x_dir is %d\r\n", x_dir);
    printf("y_dir is %d\r\n", x_dir);
    point_print(&Pen);
    point_print(&Obj);
    // assert now is x0, y0

    while( x < xEnd )
    {
        x++;
        if (x_dir)
            cycle_forward(1);
        else
            cycle_backward(1);

        if ( p < 0 ) {
            p += twoDy;
        }
        else {
            y++;
            if (y_dir)
                cycle_forward2(1);
            else
                cycle_backward2(1);

            p += twoDyMinusDx;
        }
    }

}

void point_initialize(volatile Point *p, int x, int y)
{
    p->x = x;
    p->y = y;
}

void draw_rectangle(int length)
{
    point_initialize(&Obj, length,0);
    draw();
    printf("Now is 2000,0\r\n");
    point_initialize(&Obj, length,length);
    draw();
    printf("Now is 2000,2000\r\n");
    point_initialize(&Obj, 0,length);
    draw();
    printf("Now is 0,2000\r\n");
    point_initialize(&Obj, 0,0);
    draw();
    printf("Now is 0,0\r\n");
//    cycle_backward(length);
//    cycle_backward2(length);
//    cycle_forward(length);
//    cycle_forward2(length);
}

void draw_triangle(int length)
{
    printf("Draw triangle ! \r\n ");
    point_initialize(&Obj, length,0);
    draw();
    printf("Now is %d, %d\r\n",length,0);

    point_initialize(&Obj, 0, (1.7 * length) + 0.5);
    draw();
    printf("Now is %d, %d\r\n",0,length);

    point_initialize(&Obj, -length,0);
    draw();
    printf("Now is %d, %d\r\n",-length,0);


}

void point_print(volatile Point* p)
{
    printf("(%d, %d)\r\n", p->x,p->y);
}
