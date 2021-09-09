#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_PROC 2
#define N 32
#define EVER 1

void proceso_hijo(int np);
void proceso_padre();
void llenarArreglo(int *datos);
int *reservarMemoria();
void imprimirArreglo(int *datos);
int buscarMenor(int *datos);
int buscarMayor(int *datos);

int *datos;
int main()
{
    srand(getpid());
    pid_t pid;
    printf("Probando procesos...\n");

    datos = reservarMemoria();
    llenarArreglo(datos);
    imprimirArreglo(datos);
    for (register int np = 0; np < NUM_PROC; np++)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("Error al crear el proceso...");
            exit(EXIT_FAILURE);
        }
        if (!pid)
        {
            proceso_hijo(np);
        }
    }
    proceso_padre();
    free (datos);
    return 0;
    
}

void llenarArreglo(int *datos)
{
    for (int i = 0; i < N; i++)
    {
        datos[i]=rand()%256;
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
void proceso_hijo(int np)
{
    int mayor, menor;
    printf("Ejecutando proceso hijo: %d\n", np);
    if (np == 0)
    {
        mayor = buscarMayor(datos);
        exit(mayor);
    }
    else
    {
        menor = buscarMenor(datos);
        exit(menor);
    }
    
    
     
    exit(np);
}

void proceso_padre()
{
    register int np;
    pid_t pid;
    int estado;
    for(np = 0 ; np < NUM_PROC; np++)
    {
        pid = wait(&estado);
            printf("El hijo con pid %d encontro el mayor o menor: %d\n", pid, estado>>8);
        
        
    }
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

int buscarMayor(int *datos)
{
    int mayor = 0;
    //printf("Buscando mayor");
    for (int i = 0; i < N; i++)
    {
        if (mayor <= datos[i])
            mayor = datos[i];
        //printf ("%d M ", mayor);
    }
    printf("\n");
    return mayor;
}

int buscarMenor(int *datos)
{
    int menor = 0;
    //printf("Buscando menor");
    menor = datos[0];
    for (int i = 0; i < N; i++)
    {
        if (menor >= datos[i])
            menor = datos[i];
            //printf ("%d m ", menor);}
    }
    //printf("MENOR %d\n", menor);
    
    return menor;
}

