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
pthread_mutex_t gate;
pthread_mutex_t S;
int count = 8; 

void *semgeral(void *threadarg)
{
	pthread_mutex_lock(&gate);
	pthread_mutex_lock(&S);
	count -= 1; 
	if(count>0)
	{
		pthread_mutex_unlock(&gate);
	}
	pthread_mutex_unlock(&S);
	printf("Critical Section %ld\n",(intptr_t)threadarg);
	printf("Critical Section %ld\n",(intptr_t)threadarg);
	sleep(1);
	printf("Critical Section %ld\n",(intptr_t)threadarg);
	pthread_mutex_lock(&S);
	count+=1;
	if(count==1)
 	{
		pthread_mutex_unlock(&gate);
	}
	pthread_mutex_unlock(&S);

}


int main(int argc, char *argv[]){
	int j,t,cj=0,rc;
/*	for(j=0;j<N;j++){
		printf("%lf ",a[j]);

	}
	for(j=0;j<N;j++){
		printf("%lf ",a[j]);

	}*/

	pthread_t th[max_thread];
	struct timeval  inicio, final2;
	gettimeofday(&inicio, NULL);
	pthread_mutex_unlock(&gate);
	pthread_mutex_unlock(&S);

	for(j=0;j<max_thread;j++){
	rc = pthread_create(&(th[j]),NULL, &semgeral,(void* )(intptr_t) j);	
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
