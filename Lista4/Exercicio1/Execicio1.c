#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#define N 100000000
#define max_thread 8

double pe_final;

double *a;
double *b;
pthread_mutex_t sb; 

void *calc(void *threadarg)
{
	int i,j,thid;
	double pe;
	thid =(intptr_t) threadarg;
	for(i=thid;i<N;i+=max_thread){ 	
		pe += a[i]*b[i];	
	}
	pthread_mutex_lock(&sb);
	pe_final+=pe;
	pthread_mutex_unlock(&sb);
 
}


int main(int argc, char *argv[]){
	int j,t,cj=0,rc;
	a =(double*)malloc(N*sizeof(double));
	b=(double*)malloc(N*sizeof(double));
	unsigned int seed =time(NULL);
	for(j=0;j<N;j++){
		a[j]=rand_r(&seed);
		b[j]=rand_r(&seed);
	}
/*	for(j=0;j<N;j++){
		printf("%lf ",a[j]);

	}
	for(j=0;j<N;j++){
		printf("%lf ",a[j]);

	}*/

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
		if(rc){
			printf("ERROR,%d",rc);
			exit(-1);
		}
	}
	gettimeofday(&final2, NULL);
	printf("%lf\n",pe_final);
	printf("%lf:milisegundos",(double) (1000.0 * (final2.tv_sec - inicio.tv_sec) + (final2.tv_usec - inicio.tv_usec) / 1000.0));
	return 0;
}
