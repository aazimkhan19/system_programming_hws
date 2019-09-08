#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int a, b;
int r1,r2,r3,r4;

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}
void* add(void *p){
    r1=a+b;
    pthread_exit(NULL);
}
void *subtract(void *p){
    r2= a - b;
    pthread_exit(NULL);
}
void *multiply(void *p){
    r3 = a*b;
    pthread_exit(NULL);
}
void *divide(void *p){
    r4 = a/b;
    pthread_exit(NULL);
}

int main (int argc, char* argv[]){
	long start = getMicrotime();
	if(argc==3){
		a = atoi(argv[1]);
		b = atoi(argv[2]);
	}
	else{
	    printf("arguments must be provided\n");
	    exit(0);
	}	

	pthread_t t1,t2,t3,t4;
	pthread_create(&t1,NULL, add,NULL);
	pthread_create(&t2,NULL, subtract, NULL);
	pthread_create(&t3,NULL, multiply, NULL);
	pthread_create(&t4,NULL, divide, NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);

	printf("%d + %d = %d\n",a,b,r1);
	printf("%d - %d = %d\n",a,b,r2);
	printf("%d * %d = %d\n",a,b,r3);
	printf("%d / %d = %d\n",a,b,r4);

	printf("%ld\n",getMicrotime()-start);
	pthread_exit(NULL);
}
