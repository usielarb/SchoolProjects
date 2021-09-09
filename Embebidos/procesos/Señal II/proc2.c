#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define NUM_PROC 4
#define N 32
#define EVER 1

void proceso_hijo(int np);
void proceso_padre(pid_t * pid);
void manejador (int sig);

int main()
{
    pid_t pid[NUM_PROC];
    if (signal(SIGUSR1, manejador) == SIG_ERR)
        {
            perror("Error al crear el proceso\n");
            exit(EXIT_FAILURE);
        }
    printf("Probando procesos...\n");
    for (register int np = 0; np < NUM_PROC; np++)
    {
        pid[np] = fork();
        if (pid[np] == -1)
        {
            perror("Error al crear el proceso...");
            exit(EXIT_FAILURE);
        }
        if (!pid[np])
        {
            proceso_hijo(np);
        }
    }
    proceso_padre(pid);
    return 0;
    
}

void proceso_hijo(int np)
{
    printf("Ejecutando proceso hijo: %d con pid %d\n", np, getpid());
    pause();
    printf("Se recibio una señal en el proceso hijo\n");
    
     
    exit(np);
}

void proceso_padre(pid_t * pid)
{
    register int np;
    pid_t pid2;
    int estado;
    for(np = 0 ; np < NUM_PROC; np++)
    {
        kill (pid[np], SIGUSR1 );
        sleep(3);
        pid2 = wait(&estado);
       printf("Proceso con pid %d  y retorno %d \n", pid[np], estado>>8);
        
        
    }
}

void manejador (int sig)
{
    if (sig == SIGUSR1)
    {
        printf("Señal de usuario 1 fue recibida al manejador\n");
    }
}