#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int num1=10, num2=5, res;

#define N_HILOS 4

void *funHilo(void *arg);
int main()
{
    register int nh;
    int *resultado, nhs[N_HILOS];
    pthread_t tids[N_HILOS];

    for ( nh = 0; nh < N_HILOS; nh++)
    {
        nhs[nh]=nh;
        pthread_create(&tids[nh], NULL, funHilo, (void*)&nhs[nh]);
    }
    for ( nh = 0; nh < N_HILOS; nh++)
    {
        pthread_join(tids[nh], (void **)&resultado);
        printf ("El resultado es: %d\n", *resultado);
        free(resultado);
        
    }
    
    

    return 0;

}

void *funHilo(void *arg)
{
    int nh = *(int*)arg;
    int *res = malloc(sizeof(int));
   
    if (nh == 0)
        *res = num1 + num2;
    else if(nh == 1)
        *res = num1 - num2;
    else if(nh == 2)
        *res = num1 * num2;
    else if(nh == 3)
        *res = num1 / num2;
        pthread_exit((void *)res);
}
