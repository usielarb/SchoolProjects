//Victor Usiel Arista Bojorges 
//Ordenamiento de N números con burbuja.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void llenarArreglo(int *datos, int N);
int *reservarMemoria(int N);
void imprimirArreglo(int *datos, int N);
void burbuja(int *datos, int N);


int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        perror("Introduccion de datos incorrecta...\n ./Burbuja <# de datos>\n");
        exit(EXIT_FAILURE);
    }
    int N = atoi(argv[1]);
    int *datos;
    srand(getpid());

    datos = reservarMemoria(N);
    llenarArreglo(datos, N);
    printf("\t\t<Arreglo Original>\n\n");
    imprimirArreglo(datos, N);
    burbuja(datos, N);
    printf("\t\t<Arreglo Ordenado>\n\n");
    imprimirArreglo(datos, N);
    
    free (datos);
    return 0;
    
}

void llenarArreglo(int *datos, int N)
{
    for (int i = 0; i < N; i++)
        datos[i]=rand()%1000;
}

void imprimirArreglo(int *datos, int N)
{
    for (int i = 0; i <N; i++)
    {
          if ((! (i % 14)) && i )
              printf("\n");
        printf("%3d ", datos[i]);
    }
    printf("\n\n");
}
int *reservarMemoria(int N)
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

void burbuja(int* datos, int N)
{
    int aux;
    for (int register j = 1; j < N-1; j++)
    {
        for (int register i = 0; i < N-1; i++)
        {
            if (datos[i] > datos[i+1])
            {
                aux = datos[i];
                datos[i] = datos[i+1];
                datos[i+1] = aux;
            }
        }
    }
}