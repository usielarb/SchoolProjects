#include <stdio.h>
#include "defs.h"
#include "procesamiento.h"
#include "archivos.h"
#include <stdlib.h>
#include <pthread.h>

extern pthread_mutex_t bloqueo;
extern float *hann, *pulso, *vResultado;
extern pthread_t tids[NUM_HILOS];

void * funHilo( void *arg )
{
	int nh = *(int *)arg;
    //int nucleo = nh * (N /NUM_HILOS);
    for (int register i = nh; i < N; i+=NUM_HILOS)
        vResultado[i] = pulso[i] * hann[i];
    
	pthread_exit(arg);
}
void funPadre(){
    int *hilo;
    for( int nh = 0; nh < NUM_HILOS; nh++ )
	{
		pthread_join( tids[nh], (void **)&hilo );
		printf("El hilo %d ha terminado\n", *hilo);        
	}
    guardarDatos(vResultado,"Resultado.dat");
    guardarDatos(hann, "VentanaHann.dat");
}