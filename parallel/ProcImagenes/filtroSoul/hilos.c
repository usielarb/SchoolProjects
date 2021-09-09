#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include "imagen.h"
#include "defs.h"
#include "procesamiento.h"
extern bmpInfoHeader info;
extern unsigned char *imagenGray, *imagenFiltrada;


void *funHilo(void *arg)
{
    int nhilo = *(int *)arg;
    int nucleo = (info.height - DMASK) / NUM_HILOS; 
    int inicio = nhilo * nucleo;
    int final;
    if (nhilo == NUM_HILOS - 1)
        final = info.height - DMASK;
    else
        final = inicio + nucleo;
    Sobel (inicio,final);
    pthread_exit(arg);
}
