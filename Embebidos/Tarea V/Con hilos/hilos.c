#include <stdio.h>
#include "defs.h"
#include <stdlib.h>
#include <pthread.h>

extern pthread_mutex_t bloqueo;
extern int *A, *B;
extern double PP;  
extern pthread_t tids[NUM_HILOS];

void * funHilo( void *arg )
{
    double temp = 0;
	int nh = *(int *)arg, aux, sobrantes = N % NUM_HILOS;
    int nucleo = (N /NUM_HILOS);
    int inicio = nucleo * nh;
    int fin = nucleo + inicio;
    for (int register i = inicio; i < fin; i++)
    {
        aux = A[i] * B[i];
        temp += aux ;
    }
    for( int register i = 0; i < sobrantes && nh == NUM_HILOS - 1; i++)
    {
        aux = A[(N- sobrantes) + i] * B[(N- sobrantes) + i];
        temp += aux ;
    }
    pthread_mutex_lock(&bloqueo);
    PP += temp;
    pthread_mutex_unlock(&bloqueo);
	pthread_exit(arg);  
}
void funPadre(){
    int *hilo;
    for( int nh = 0; nh < NUM_HILOS; nh++ )
	{
		pthread_join( tids[nh], (void **)&hilo );
		printf("El hilo %d ha terminado\n", *hilo);        
	}
    printf("Resultado del producto punto es: \t%.0lf\n", PP);

}