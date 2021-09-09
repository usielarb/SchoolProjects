#include <stdio.h>
#include "defs.h"
#include "procesamiento.h"
#include "archivos.h"
#include <stdlib.h>
#include <pthread.h>

//extern pthread_mutex_t bloqueo;
extern float *hann, *pulso, *vResultado, *autocorelacion;
extern pthread_t tids[NUM_HILOS];

void * funHilo( void *arg )
{
	int nh = *(int *)arg;
    //int nucleo = nh * (N /NUM_HILOS);
    for (int register i = nh; i < N; i+=NUM_HILOS)
        vResultado[i] = pulso[i] * hann[i];
	pthread_exit(arg);
}
void * funHilo2( void *arg )
{
	int nh = *(int *)arg;
    int register i, j;
    float temp = 0;    
    //int nucleo = nh * (N /NUM_HILOS);
    for (i = nh; i < N; i+=NUM_HILOS, temp = 0)
    {
        for (j = i ; j < N - 1 ; j++)
            temp += vResultado[j] * vResultado [j-i];
        autocorelacion[i] = temp;
    }

	pthread_exit(arg);
}

void funPadre(){
    int *hilo;
    for( int nh = 0; nh < NUM_HILOS; nh++ )
	{
		pthread_join( tids[nh], (void **)&hilo );
		printf("El hilo %d de ventana ha terminado\n", *hilo);        
	}
    guardarDatos(vResultado,"Resultado.dat");
    guardarDatos(hann, "VentanaHann.dat");
}
void funPadre2(){
    int *hilo;
    for( int nh = 0; nh < NUM_HILOS; nh++ )
	{
		pthread_join( tids[nh], (void **)&hilo );
		printf("El hilo %d  de autocorelacion ha terminado\n", *hilo);        
	}
    guardarDatos(autocorelacion,"Autocorelacion.dat");
}