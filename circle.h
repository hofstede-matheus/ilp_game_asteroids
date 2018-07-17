#include "rectangle.h"

typedef struct{
    int x;
    int y;
    int r;
} tCircle;


tCircle createCircle(int x, int y, int r);
int intersectsCircle(tRectangle range, tCircle point);
int containsPoint(tCircle circle, int x, int y);