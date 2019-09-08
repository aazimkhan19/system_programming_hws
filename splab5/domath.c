#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main(int argc, char *argv[]){
	long start = getMicrotime();	
	int a=0;
	int b=1;
	if(argc==3){
		a = atoi(argv[1]);
		b = atoi(argv[2]);
	}
	else{
	    printf("arguments must be provided\n");
	    exit(0);
	}
    
	
	int child1=fork();
	if(child1==0){
	    printf("child1: %d + %d = %d\n", a, b, a+b);
	    exit(0);
	}
	
	int child2=fork();
	if(child2==0){
	    printf("child2: %d - %d = %d\n", a, b, a-b);
	    exit(0);
	}
	
	int child3=fork();
	if(child3==0){
	    printf("child3: %d * %d = %d\n", a, b, a*b);
	    exit(0);
	}
	
	int child4=fork();
	if(child4==0){
	    printf("child4: %d / %d = %d\n", a, b, a/b);
	    exit(0);
	}
	
	for(int i=0;i<4;i++)
	    wait(NULL);
	printf("parent: done.\n");
	printf("%ld\n",getMicrotime()-start);
} 
