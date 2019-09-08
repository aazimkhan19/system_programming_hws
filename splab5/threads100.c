#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
void *nothing(){
	pthread_exit(NULL);
}

int main(){
	long start = getMicrotime();
    pthread_t tids[100];
    for(int i=0; i<100; i++){
        pthread_create(&tids[i],NULL, nothing, NULL);
	}
    for(int i = 0; i < 100; i++){
        pthread_join(tids[i],NULL);
    }
	printf("%ld\n",getMicrotime()-start);
}
