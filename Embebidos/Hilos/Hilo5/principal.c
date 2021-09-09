#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "defs.h"
#include "hilos.h"
#include "helper.h"

int *datos;
pthread_mutex_t bloqueo;
int res[3];

int main()
{    
    register int nh;
    char sentencia[3][12] = {"Promedio", "N de Pares", "N de Primos"};
	pthread_t tids[NUM_HILOS];
	int nhs[NUM_HILOS], *hilo;
	pthread_mutex_init(&bloqueo, NULL);
    srand(getpid());
 
    datos = reservarMemoria();
    llenarArreglo(datos);
	printf("Arreglo original\n");
    imprimirArreglo(datos);


	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		nhs[nh] = nh;
		//nhs[0] = 0;
		//nhs[1] = 1;
		//nhs[2] = 2;
		//nhs[3] = 3;
        //printf("----\n");
		pthread_create( &tids[nh] , NULL, funHilo, (void *)&nhs[nh] );
	}

	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		pthread_join( tids[nh], (void **)&hilo );
		printf("El hilo %d ha terminado\n", *hilo);
        if (nh)
            printf ("El resultado de el %s es: %d \n", sentencia[nh - 1], res[nh - 1]);
        else
        {
            printf("El arreglo ordenado es: \n");
            imprimirArreglo(datos);
        }
        
	}
	pthread_mutex_destroy(&bloqueo);
	return 0;

}
