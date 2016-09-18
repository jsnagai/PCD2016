/*
 * =====================================================================================
 *
 *       Filename:  exercicio11.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  23/08/2016 11:14:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#define N 10000
#define max_threads 16


int main(){
	double pe_local=0.0,pe;
	int i,j;
	double *arr1,*arr2;
	arr1 = (double*)malloc(N*sizeof(double));
	arr2 = (double*)malloc(N*sizeof(double));

	unsigned int seed=time(NULL);

	double start, end;
	omp_set_num_threads(max_threads); 
	int aux;
	for(i=0;i<N;i++){
		arr1[i]=1;
		arr2[i]=1;

	}
	start = omp_get_wtime();
#pragma omp parallel default(none) private(j) shared(arr1,arr2) reduction(+:pe)
	{
#pragma omp for 	
		for(j=0;j<N;j++){
			pe += arr1[j]*arr2[j];
		}
	}

	end = omp_get_wtime();
	printf("produto escalar: %lf tempo : %lf",pe,end-start);

	return 0;

}





