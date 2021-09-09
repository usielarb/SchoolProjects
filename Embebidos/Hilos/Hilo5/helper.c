#include <stdlib.h>
#include "defs.h"
#include <stdio.h>
extern int *datos;
void llenarArreglo()
{
    for (int i = 0; i < N; i++)
    {
        datos[i]=rand()%255;
    }
    
}
void imprimirArreglo()
{
    for (int i = 0; i <N; i++)
    {
          if (! (i % 16))
              printf("\n");
        printf("%3d ", datos[i]);
    }
    printf("\n");

    
}


int *reservarMemoria()
{
    int *mem;
    mem = (int *)malloc(N*sizeof(int));
    if (!mem)
    {
        perror("Error al asignar memoria...");
        exit(EXIT_FAILURE);
    }
    return mem;
}
