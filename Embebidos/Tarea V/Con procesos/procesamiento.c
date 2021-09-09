#include <stdio.h>
#include "defs.h"
#include <math.h>

void genera_seno(float seno[]){
    float f = 1000, fs =45000;
    register int n;
    for (n = 0; n < N; n++)
    {
        seno[n] = sinf (2 *  M_PI * f * n / fs);
    }
}
void generaHann(float ventana[])
{
    float a0 = 0.5, a1 = 0.5;
    int register n;
    for ( n = 0; n < N; n++)
    {
        ventana[n] = a0 - (a1 *  cosf ((2 * M_PI * n) / (N - 1)));
    }
}