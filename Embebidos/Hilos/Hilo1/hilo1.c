#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int num1=10, num2=5;
void *suma(void *arg);
void *resta(void *arg);
void *multiplicacion(void *arg);
void *division(void *arg);

int main()
{
    int *res_suma, *res_resta, *res_multi, *res_divi;
    pthread_t tid_suma, tid_resta, tid_multi, tid_divi;
    
    pthread_create(&tid_suma, NULL, suma, NULL);
    pthread_create(&tid_resta, NULL, resta, NULL);
    pthread_create(&tid_multi, NULL, multiplicacion, NULL);
    pthread_create(&tid_divi, NULL, division, NULL);

    pthread_join(tid_suma, (void **)&res_suma);
    pthread_join(tid_resta,(void **)&res_resta);
    pthread_join(tid_multi,(void **)&res_multi);
    pthread_join(tid_divi,(void **)&res_divi);

    printf ("El resultado de la suma es: %d\n", *res_suma);
    printf ("El resultado de la resta es: %d\n", *res_resta);
    printf ("El resultado de la multi es: %d\n", *res_multi);
    printf ("El resultado de la divi es: %d\n", *res_divi);

    free (res_multi);
    free (res_divi);

    return 0;

}

void *suma(void *arg)
{
    static int res;
    res = num1 + num2;
    pthread_exit((void*)&res);
}
void *resta(void *arg)
{
    static int res;
    res = num1 - num2;
    pthread_exit((void*)&res);
}
void *multiplicacion(void *arg)
{
    int *res = (int *)malloc(sizeof(int ));
    *res = num1 * num2;
    pthread_exit((void*)res);
}
void *division(void *arg)
{
    int *res = (int *)malloc(sizeof(int ));
    *res = num1 / num2;
    pthread_exit((void*)res);
}