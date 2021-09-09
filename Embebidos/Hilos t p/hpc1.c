#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUM_HILOS 4
#define N 16

int *A, *B, *C;


void * funHilo( void * arg );
int *reservarMemoria();
void llenarArreglo(int *datos);
void imprimirArreglo(int *datos);

int main()
{
	int *hilo;
	pthread_t tids[NUM_HILOS];
	int nhs[NUM_HILOS];
	register int nh;

	A = reservarMemoria();
	B = reservarMemoria();
	C = reservarMemoria();

	llenarArreglo(A);
	llenarArreglo(B);

	imprimirArreglo(A);
	imprimirArreglo(B);
	imprimirArreglo(C);

	printf("Probando hilos...\n");

	for( nh = 0; nh < NUM_HILOS; nh++ )
	{
		//nhs[0] = 0;
		//nhs[1] = 1;
		//nhs[2] = 2;
		//nhs[3] = 3;
		//printf ("<<<<%d\n", nh);
		nhs[nh] = nh;
		pthread_create( &tids[nh], NULL, funHilo, &nhs[nh] );
		//printf (">>>>>%d\n", nh);
	}

	for( nh = 0; nh < NUM_HILOS; nh++ )
	{

		pthread_join( tids[nh],  (void **)&hilo);
		printf("La hilo %d termino\n", *hilo);
	}

	printf("EL resultado de la multiplicacion quedo de la siguiente manera\n");
	imprimirArreglo(A);
	imprimirArreglo(B);
	imprimirArreglo(C);


	free(A);
	free(B);
	free(C);
	return 0;
}

void * funHilo( void * arg )
{
	int nh = *(int *)arg;
	int register i;
	printf("Hilo %d en ejecucion \n", nh);
	
	for (i = nh; i < N ; i+= NUM_HILOS)
	{
		C[i] = A[i] * B[i];
	}
	
	pthread_exit( arg );
}
// void * funHilo( void * arg )
// {
// 	int nh = *(int *)arg;
// 	int register i;
// 	int tamBloque = N / NUM_HILOS;
// 	printf("Hilo %d en ejecucion \n", nh);
	
// 	for (i = nh * tamBloque; i < (nh + 1) * tamBloque; i++)
// 	{
// 		C[i] = A[i] * B[i];
// 	}
	
// 	pthread_exit( arg );
// }



void llenarArreglo(int *datos)
{
    for (int i = 0; i < N; i++)
    {
        datos[i]=rand()%10;
    }
    
}
void imprimirArreglo(int *datos)
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


