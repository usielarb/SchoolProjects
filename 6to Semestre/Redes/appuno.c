#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread(void*);
int *llenarm(int*);

int main(int argc,char *argv[]){
	if(argc<2){
		printf("Error ejecuta como %s <numero>\n",*argv);
		exit(1);
	}
	int p=atoi(*(argv+1)),i,*j;
	pthread_t *t;
	j=(int*)malloc(sizeof(int)*p);
	t=(pthread_t*)malloc(sizeof(pthread_t)*p);
	for(i=0;i<p;i++){
		*(j+i)=i;
		pthread_create(&(*(t+i)),NULL,thread,(void*)&(*(j+i)));
	}
	printf("Proceso padre\n");
	for(i=0;i<p;i++){
		pthread_join(*(t+i),NULL);
	}

	free(t);
	free(j);
	return 0;
}

void *thread(void *arg){
	printf("Hilo id %ld hijo con argumento %d\n",pthread_self(),*((int*)arg));
}

int main(int argc,char *argv[]){
    int fx, fy, cx, cy;
    scanf("%d %d %d %d", &fx, &fy, &cx
}   


int *llenarm(int* m, int n, int m)
{
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            
}
}


