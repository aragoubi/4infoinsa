#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

double f(double x);
int main (int argc, char *argv[])
{
	if(argc < 2){
		printf("Usage : tp4 n");
		return 1;
	}

	int n = atoi(argv[1]);
	
	if(n <= 0){
		printf("n doit être supérieur à 0\n");
		return 1;
	}

	double pi;
	int i;
	double somme = 0;
	for(i = 1; i <= n; i++){
		somme += f((i-1)/(n+0.0)) + f(i/(n+0.0));
	}
	
	pi = somme/(2.0*n);
	
	printf("PI = %f\n", pi);

	return 0;
}

double f(double x){
	return (4/(1+x*x+0.0));
}
