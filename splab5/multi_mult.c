#include<stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>


int A[100][100];
int B[100][100];
int C[100][100];

int n = 0;

struct data{
	int g_i;
	int g_j;
};

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
void* add(void *p){
	
	struct data *ind=(struct data*)p;
	int i=ind->g_i;
	int j=ind->g_j;
	for(int k=0;k<n;k++){
			C[i][j]=C[i][j]+A[i][k]*B[k][j];
	}
	pthread_exit(NULL);
}

int main(int argc,char **argv){
	long start = getMicrotime();
	srand(time(0));
	if(argc==2){
		n = atoi(argv[1]);
	}
	else{
	    printf("arguments must be provided\n");
	    exit(0);
	}
	
	pthread_t t[n];
	int lower = 5, upper = 10;
    
    for(int i=0;i<n;i++){
    	for(int j=0;j<n;j++){
			A[i][j]=rand()%upper;
		 	B[i][j]=rand()%upper;
  		}
    }


	printf("A:\n");
    for(int i=0;i<n;i++){
    	for(int j=0;j<n;j++){
			printf("%d ",A[i][j]);
  		} 
    	printf("\n");
    }
    printf("\n");
	
	printf("B:\n");
    for(int i=0;i<n;i++){
    	for(int j=0;j<n;j++){
     		printf("%d ",B[i][j]);
  		} 
    	printf("\n");
    }
    printf("\n");

	struct data arg[n];
	int ind=0;
	for(int i=0;i<n;i++){	
		for(int j=0;j<n;j++){
			arg[ind].g_i=i;
			arg[ind].g_j=j;
			pthread_create(&t[ind],NULL,add,(void*)&arg[ind]);
			ind++;			
		}
	}

	ind=0;
	for(int i=0;i<n;i++){	
		for(int j=0;j<n;j++){
			pthread_join(t[ind],NULL);
			ind++;			
		}
	}	

	printf("C: \n");
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("%d ",C[i][j]);
		}
		printf("\n");
	}
	printf("time %ld\n",getMicrotime()-start);
	return 0;
}
