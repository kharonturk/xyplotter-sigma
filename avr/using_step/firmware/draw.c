
#include "motor.h"
#include "draw.h"
#include <stdio.h>

#define abs(x) ( (x>0)? (x):(-x))

volatile Point Pen;
volatile Point Obj;

void draw()
{
    Point diff;
    float m;
    if ( (Pen.x == Obj.x)
            && (Pen.y == Obj.y))
        return;

    diff.x = Obj.x - Pen.x;
    diff.x = abs(diff.x);
    diff.y = Obj.y - Pen.y;
    diff.y = abs(diff.y);


    if ( diff.x > diff.y)
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
    int dir = 0;

    if ( x0 > xEnd ) {
        x = xEnd;
        y = yEnd;
        xEnd = x0;
        dir = 0;
    }

    else {
        x = x0;
        y = y0;
        dir = 1;
    }

    // assert now is x0, y0

    while( x < xEnd )
    {
        x++;

        if ( p < 0 ){
            p += twoDy;
            if (dir)
                cycle_forward2(1);
            else
                cycle_backward2(1);
        }
        else {
            y++;
            if (dir)
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
    int x, y;
    int dir = 0;

    if ( x0 > xEnd ) {
        x = xEnd;
        y = yEnd;
        xEnd = x0;
        dir = 0;
    }

    else {
        x = x0;
        y = y0;
        dir = 1;
    }

    // assert now is x0, y0

    while( x < xEnd )
    {
        x++;

        if ( p < 0 ) {
            p += twoDy;
            if (dir)
                cycle_forward(1);
            else
                cycle_backward(1);
        }
        else {
            y++;
            if (dir)
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

}
