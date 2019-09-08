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
	if(child1==0){
	    execlp("python","python","add.py",argv[1],argv[2],NULL);
	    exit(0);
	}
	
	int child2=fork();
	if(child2==0){
	    execlp("java","java","Subtract",argv[1],argv[2],NULL);
	    exit(0);
	}
	
	int child3=fork();
	if(child3==0){
	    execlp("node","node","multiply.js",argv[1],argv[2],NULL);
	    exit(0);
	}
	
	int child4=fork();
	if(child4==0){
	    execlp("bash","bash","divide.sh",argv[1],argv[2],NULL);
	    exit(0);
	}
	
	for(int i=0;i<4;i++)
	    wait(NULL);
	printf("parent: done.\n");
} 
