#include "utils.h"

int Max(int i, int j){ if (i >= j){return i;}else{return j;} }
int Min(int i, int j){ if (i >= j){return j;}else{return i;} }
int CollisionCheck(int bx,int ex,int by, int ey,int bw,int bh,int ew,int eh)
{
    return (Max(bx,ex) < Min(bx + bw, ex+ew)) && (Max(by,ey) < Min(by + bh, ey+eh));
}

void calcSlope(int x1,int y1,int x2,int y2, float *dx, float *dy)
{
    int steps = Max(abs(x1-x2),abs(y1-y2));
    if(steps == 0)
    {
        *dx = *dy = 0;
        return;
    }
    *dx = (x1-x2);
    *dx /= steps;

    *dy = (y1 - y2);
    *dy /= steps;
}
