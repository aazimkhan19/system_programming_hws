#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int a = 6;
	int b = 3;
	if(argc==3){
		a = atoi(argv[1]);
		b = atoi(argv[2]);
	}
    
	int child1 = fork();
	if (child1 < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} 
	else if (child1 == 0) {
		printf("child1: %d + %d = %d\n", a, b, a+b);
	} 
	else {
		wait(NULL);
		
		int child2 = fork();
	    	if (child2 < 0) {
	    		fprintf(stderr, "fork failed\n");
	    		exit(1);
	    	} 
	    	else if (child2 == 0) {
	    		printf("child2: %d - %d = %d\n", a, b, a-b);
	    	} 
	    	else {
	    		wait(NULL);
	    		
	    		int child3 = fork();
			if (child3 < 0) {
				fprintf(stderr, "fork failed\n");
				exit(1);
			} 
			else if (child3 == 0) {
				printf("child3: %d * %d = %d\n", a, b, a*b);
			} 
			else {
				wait(NULL);
				
				int child4 = fork();
			    	if (child4 < 0) {
			    		fprintf(stderr, "fork failed\n");
			    		exit(1);
			    	} 
			    	else if (child4 == 0) {
			    		printf("child4: %d / %d = %d\n", a, b, a/b);
			    	}
			    	else{
			    	    	wait(NULL);
					printf("parent: done.\n");
            			}		
        		}
    		}
	}
	return 0;
}
