#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_HILOS 4

void * funHilo( void *arg );
int contador;
pthread_mutex_t bloqueo;

int main()
{
	register int nh;
	pthread_t tids[NUM_HILOS];
	int nhs[NUM_HILOS], *hilo;
	contador = 0;

	printf("Ejemplo de hilos\n");

	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		nhs[nh] = nh;
		//nhs[0] = 0;
		//nhs[1] = 1;
		//nhs[2] = 2;
		//nhs[3] = 3;
		pthread_create( &tids[nh] , NULL, funHilo, (void *)&nhs[nh] );
	}

	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		pthread_join( tids[nh], (void **)&hilo );
		printf("El hilo %d ha terminado\n", *hilo);
	}
	pthread_mutex_destroy(&bloqueo);
	return 0;
}

void * funHilo( void *arg )
{
	int nh = *(int *)arg;
	register int i;
	// int prueba = pthread_mutex_trylock(&bloqueo);
	// printf("<%d>\n", prueba);
	pthread_mutex_lock(&bloqueo);
	contador++;
	printf("Hilo %d en ejecucion con contador: %d \n", nh, contador); 

	while ((--i));

	contador++;
	printf("Hilo %d en ejecucion con contador: %d \n", nh, contador); 
	pthread_mutex_unlock(&bloqueo);
	pthread_exit(arg);
}


