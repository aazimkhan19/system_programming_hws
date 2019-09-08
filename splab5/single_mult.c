#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
int main (int argc, char* argv[]){
	long start = getMicrotime();
	srand(time(0));

	int n = 0;	
	if(argc==2){
		n = atoi(argv[1]);
	}
	else{
	    printf("arguments must be provided\n");
	    exit(0);
	}
    
	int A[n][n];
    int B[n][n];
    int C[n][n];
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


    printf("C:\n");
    for(int i=0;i<n;i++){
    	for(int j=0;j<n;j++){
        	C[i][j]=0;
            for(int k=0;k<n;k++)
            	C[i][j]=C[i][j]+(A[i][k]*B[k][j]);
            printf("%d ",C[i][j]);
         }
         printf("\n");
    }
	
	printf("%ld\n",getMicrotime()-start);
	return 0;
}
