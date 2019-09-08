#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/time.h>

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

int main(){
	long start = getMicrotime();
	int n=100;
    pid_t pids[n];
    
	for(int i = 0; i < n; i++){
		if ((pids[i] = fork()) < 0) {
			perror("fork");
			abort();
		} 
		else if (pids[i] == 0) {
			exit(0);
		}
	}

	for(int i=0;i<n;i++)
	    wait(NULL);
	printf("%ld\n",getMicrotime()-start);
    return 0;
}
