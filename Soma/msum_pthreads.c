#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#define N 1000
#define max_thread 1

double **arr1;
double **arr2;
double **arrR;


void *calc(void *threadarg)
{
	int sum=0,i,j,thid;
	thid =(intptr_t) threadarg;
	unsigned int seed =time(NULL);
	for(i=thid;i<N;i+=max_thread){ 	
		for(int j=0;j<N;j++){
			arrR[i][j]=arr1[i][j]+arr2[i][j];
		}
	}
}


int main(){
	int j,t,cj=0,rc;
	unsigned int seed = time(NULL);
	arr1=(double**)malloc(N*sizeof(double*));
	arr2=(double**)malloc(N*sizeof(double*));
	arrR=(double**)malloc(N*sizeof(double*));
	for(j=0;j<N;j++){
			arr1[j]=(double*)malloc(N*sizeof(double));
			arr2[j]=(double*)malloc(N*sizeof(double));
			arrR[j]=(double*)malloc(N*sizeof(double));

	}
	pthread_t th[max_thread];
	for(t=0;t<N;t++){
		for(j=0;j<N;j++){
			arr1[t][j]=rand_r(&seed)%100;
			arr2[t][j]=rand_r(&seed)%100;
			

		}
	}
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
	printf("%lf:milisegundos\n",(double)(1000 * (final2.tv_sec - inicio.tv_sec) + (final2.tv_usec - inicio.tv_usec) / 1000));
	return 0;
}
