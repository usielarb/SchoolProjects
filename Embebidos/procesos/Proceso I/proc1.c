#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    float num1= 45, num2 = 13, suma, resta ;
    pid_t pid;
    int status;
    printf("Probando procesos...\n");
    pid = fork();
    if (pid == -1)
    {
        perror("Error al crear el proceso...");
        exit(EXIT_FAILURE);
    }
    if (!pid)
    {
        printf("proceso hijo ejecutandocon pid %d\n", getpid());
        suma = num1 + num2 ;
        printf("La suma es: %f\n", suma);
        exit(3);
    }
    else
    {
        sleep (10);
        printf("proceso padre ejecutandocon pid %d\n", getpid());
        resta = num1 - num2 ;
        printf("La resta es: %f\n", resta);
        // el wait quita el estado zombie al proceso hijo qu elo tenga esperando.
        pid = wait(&status);
        printf ("Proceso terminado con pid: %d y estado: %d \n", pid, status>>8);
    }
    return 0;
    
}