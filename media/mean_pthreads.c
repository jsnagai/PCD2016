#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#define N 10000000
#define max_thread 1

double *redthread;

int *arr;


void *calc(void *threadarg)
{
	int sum=0,i,j,thid;
	thid =(intptr_t) threadarg;
	unsigned int seed =time(NULL);
	for(j=thid;j<N;j+=max_thread){
		arr[j]=rand_r(&seed);
	}
	for(i=thid;i<N;i+=max_thread){ 	
		sum += arr[i];
	}
	redthread[thid]=sum;
}


int main(){
	int j,t,cj=0,rc;
	double fsum=.0;
	arr =(int*)malloc(N*sizeof(int));
	redthread = (double*)malloc(max_thread*sizeof(double));
	pthread_t th[max_thread];
	struct timeval  inicio, final2;
	gettimeofday(&inicio, NULL);
	for(j=0;j<max_thread;j++){
		rc = pthread_create(&(th[j]),NULL, &calc	,(void* )(intptr_t) j);	
		if(rc){
			printf("ERROR,%d",rc);
			exit(-1);
		}

	}
	for(j=0; j<max_thread; j++) {
		rc = pthread_join(th[j],NULL);
		fsum+=redthread[j];
		if(rc){
			printf("ERROR,%d",rc);
			exit(-1);
		}
	}
	gettimeofday(&final2, NULL);
	printf("%lf\n",fsum/N);
	printf("%d:milisegundos",(int) (1000 * (final2.tv_sec - inicio.tv_sec) + (final2.tv_usec - inicio.tv_usec) / 1000));
	return 0;
}
