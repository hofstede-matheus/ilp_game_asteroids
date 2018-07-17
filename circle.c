
#include <math.h>
#include "circle.h"


tCircle createCircle(int x, int y, int r){
    tCircle circle;
    circle.x = x;
    circle.y = y;
    circle.r = r;

    return circle;
}

int intersectsCircle(tRectangle range, tCircle circle){
    int xDist = abs(range.x - circle.x);
    int yDist = abs(range.y - circle.y);

    int r = circle.r;

    int w = range.w;
    int h = range.h;

    int edges = pow((xDist - w), 2) + pow((yDist - h), 2);

    // sem intersecção
    if( xDist > (r + w) || yDist > (r + h) ) return 0;
    // com intersecção
    if( xDist <= w || yDist <= h ) return 1;
    // com intersecção no canto    
    if(edges <= r*r) return 1;

}

int containsPoint(tCircle circle, int x, int y){
    int d = pow((x - circle.x), 2) + pow((y - circle.y), 2);
    if (d <= circle.r * circle.r) return 1;
    else return 0; 
}