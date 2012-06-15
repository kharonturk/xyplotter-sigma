
#ifndef _PLOTTER_DRAW_H_
#define _PLOTTER_DRAW_H_

void draw_rectangle();
void draw_triangle();
void draw_circle();

typedef struct point
{
    int x;
    int y;
} Point;

extern volatile Point Pen;
extern volatile Point Obj;

void point_initialize(volatile Point *p, int x, int y);
void draw();
void lineBres_more_1(int, int, int, int);
void lineBres_less_1(int, int, int, int);
void point_print(volatile Point* p);

#endif
