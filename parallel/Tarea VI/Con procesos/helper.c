#include <stdlib.h>
#include "defs.h"
#include <stdio.h>

void llenarArreglo(float datos[])
{
    for (int i = 0; i < N; i++)
    {
        datos[i]=rand()%255;
    }
    
}
void imprimirArreglo(float datos[])
{
    for (int i = 0; i <N; i++)
    {
          if (! (i % 16))
              printf("\n");
        printf("%3f ", datos[i]);
    }
    printf("\n");

    
}


float *reservarMemoria()
{
    float *mem;
    mem = (float *)malloc(N*sizeof(float));
    if (!mem)
    {
        perror("Error al asignar memoria...");
        exit(EXIT_FAILURE);
    }
    return mem;
}
