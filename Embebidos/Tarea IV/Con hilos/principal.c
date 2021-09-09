#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "defs.h"
#include "hilos.h"
#include "archivos.h"
#include "helper.h"
#include "procesamiento.h"

float *hann, *pulso, *vResultado;
pthread_t tids[NUM_HILOS];

int main()
{    
    register int nh;
	int nhs[NUM_HILOS], *hilo;
    srand(getpid());
 
    hann = reservarMemoria();
    pulso = reservarMemoria();
	vResultado = reservarMemoria();

	leerDatos(pulso, "PulseSensor.dat");
	generaHann(hann);



	

    //imprimirArreglo(datos);


	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		nhs[nh] = nh;
		pthread_create( &tids[nh] , NULL, funHilo, (void *)&nhs[nh] );
		printf("todo kul\n");
	}

	funPadre();
	
	
	
	return 0;

}
