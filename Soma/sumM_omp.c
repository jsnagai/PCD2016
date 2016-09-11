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
#define N 1000
#define max_threads 8

double **arr1;
double **arr2;
double **res;

void mprint(double **matrix){
	int i,j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%lf ",matrix[i][j]);

		}
		printf("\n");
	}
	printf("\n\n");


}

int main(){
	int sum;
	int i,j;
	arr1 = (double**)malloc(N*sizeof(double*));
	arr2 = (double**)malloc(N*sizeof(double*));
	res = (double**)malloc(N*sizeof(double*));

	unsigned int seed=time(NULL);
	double k = 0.1;

	for(i=0;i<N;i++){
		arr1[i]=(double*)malloc(N*sizeof(double));
		arr2[i]=(double*)malloc(N*sizeof(double));
		res[i]=(double*)malloc(N*sizeof(double));

	}
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			arr1[i][j]=rand_r(&seed)%100;
			arr2[i][j]=rand_r(&seed)%100;

		}
	}

double start, end;
omp_set_num_threads(max_threads); 
int aux;
start = omp_get_wtime();
#pragma omp parallel default(none) shared(arr1,arr2,res)  private(i,j)  
{
#pragma parallel for
for(j=0;j<N;j++){
		for(i=0;i<N;i++){
			res[j][i]=arr1[j][i]+arr2[j][i];
		}
	}	

}
end = omp_get_wtime();

printf("%lf:ms",end-start);

return 0;

}





