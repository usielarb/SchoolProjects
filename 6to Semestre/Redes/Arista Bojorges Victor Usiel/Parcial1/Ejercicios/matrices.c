#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
struct matriz {
	int ** mat;
    int x;
    int y;
};
typedef struct matriz mat;

struct parametros
{
    int inicio;
    int final;
};
typedef struct parametros para;

void gen_mat(mat *a, int x, int y);
void asig_dim(mat **a,int x ,int y);
void imp_mat(mat *a, int x, int y);
void *multi(void* arg);


mat *a;
mat *b;
mat *c;
int main(int argc, char *argv[]){
    int i, x, y, z, res, npr, hilos, ini, fin;
    srand(time(NULL));

    if (argc < 2)
        printf ("No se han introducido los datos requeridos");
    else{
        x = atoi(*(argv + 1));
        y = atoi(*(argv + 2));
        z = atoi(*(argv + 3));
        hilos = atoi(*(argv + 4));
        if (hilos>y)
            hilos=y;
        pthread_t *t;
        para *par;

        t =(pthread_t*)malloc(sizeof(pthread_t)*hilos);
        par = (para*)malloc(sizeof(para)*hilos);
        printf ("{ %d, %d, %d, %d\n", x, y, z, hilos);
        res = x % hilos;
        npr = (x - res) / hilos;
        printf("%d ## %d\n",res, npr);
        asig_dim(&a,x,y);
        asig_dim(&b,y,z);
        asig_dim(&c,z,x);

        gen_mat(a,x, y);
        gen_mat(b,y,z);

        for (i = 0, ini = 0; i < hilos; i++)
        {
            fin = ini + npr - 1;
            if (i < res) fin++;

            (par+i)->inicio = ini;
            ((par+i)->final) = fin;
            printf("%d ---%d, %d\n",i,(par+i)->inicio,(par+i)->final);
            pthread_create(&(*(t+i)), NULL,multi, (void*)&(*(par+i)) );
            ini=fin+1;

        }
        for(i=0;i<hilos;i++)
		    pthread_join(*(t+i),NULL);
	
        imp_mat(a,a->x,a->y);
        imp_mat(b,b->x,b->y); 
        imp_mat(c,c->x,c->y);
        free (t);
        free (par);
    }
}

void asig_dim(mat **b,int x ,int y){
    mat *a;
    a=(mat*)malloc(sizeof(mat));
    int i;
    a->x=x;
    a->y=y;
    a->mat=(int**)malloc(y*sizeof(int*));
    for(i=0;i<y;i++){
        a->mat[i]=(int*)malloc(x*sizeof(int));
    }
    *b=a;
}

void gen_mat(mat* a, int x, int y){
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
            a->mat[i][j] = rand() % 5;
           
    }
}
void imp_mat(mat* a, int x, int y){
    printf ("\n");
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
            printf ("%d ", a->mat[i][j]);
        printf("\n");
    }
}
void *multi(void* arg)
{
    
    
    printf("hilo");
    int suma=0, k;
        para *aux;
        aux = (para*)arg;
        printf ("\n%d %d\n", aux->inicio, aux->final);
    
        int i, j;
        i=aux->final;
        j=aux->inicio;
        //c->mat[i][j]=1;
    


        printf ("%d %d\n", a->y, b->x);

        for (i = aux->inicio; i <= aux->final; i++)
        {   
            for (k = 0; k < a->y; k++)
            {
                for (j = 0, suma = 0; j < b->x; j++)
                {
                    suma+=a->mat[i][j]*b->mat[j][k];
                    //printf("%d  ", suma);
                }
                c->mat[i][k]=suma;
            }
            //printf("%d-", a->mat[i][k]);
        }
        printf("--");
}
