#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
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
	printf("%d\n",child1);
	if(child1==0){
	printf("%d id\n:",getpid());
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
} 
