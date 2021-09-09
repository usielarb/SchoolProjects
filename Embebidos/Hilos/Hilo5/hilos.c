#include <stdio.h>
#include "defs.h"
#include "procesamiento.h"
#include <stdlib.h>
#include <pthread.h>

extern pthread_mutex_t bloqueo;
extern int *datos;
extern int res[3];

void * funHilo( void *arg )
{
	int nh = *(int *)arg;
    pthread_mutex_lock(&bloqueo);
	//printf(">>>>%d\n", nh);

    if (nh == 0)
        burbuja(datos);
    else if (nh == 1)
        res[0] = sacarPromedio(datos);
    else if (nh == 2)
        res[1] = contarPares(datos);
    else if (nh == 3)
        res[2] = contarPrimos(datos);

	pthread_mutex_unlock(&bloqueo);
    //printf ("%d -> %d ", nh, res[nh-1]);
	pthread_exit(arg);
}