#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int numOfPassengers = 4;
int numOfCars = 1;
int waitTime = 5;
int runTime = 60;
int numOfSeats = 2;

sem_t available;
sem_t entered;
sem_t filled;
sem_t free_;

struct identifier{
	int id;
};

void wait(sem_t *x,char s[]){
	int n = sem_wait(x);
	printf("%s\n",s);
}

void signal(sem_t *x,char s[]){
	int n = sem_post(x);
	printf("%s\n",s);
}

void* passenger(void *p){
	srand(time(0));
	struct identifier *ind=(struct identifier*)p;
	int ID=ind->id;
	while(1){
		sleep(1+rand()%waitTime);
        printf("passenger %d boarding\n",ID);
        wait(&available,"enter");
        signal(&entered,"taken");
        wait(&filled,"inside");
        printf("passenger %d is running\n",ID);
        wait(&free_,"free");
        printf("passenger %d unboarding\n",ID);
	}
}

void* car(void *p){
	srand(time(0));
	struct identifier *ind=(struct identifier*)p;
	int ID=ind->id;
	while(1){
		printf("car %d loading\n",ID);
        for(int i=0; i<numOfSeats; i++)
            signal(&available,"ready");
        for(int i=0; i<numOfSeats; i++)
            wait(&entered,"OK");
        for(int i=0; i<numOfSeats; i++)
            signal(&filled,"reserved");
        printf("car %d is running\n",ID);
        sleep(1+rand()%waitTime);
        printf("car %d unloading\n",ID);
        for(int i=0; i<numOfSeats; i++)
            signal(&free_,"opened");
	}
}

int main(int argc, char *argv[]){
	sem_init(&available, 0, 0);
	sem_init(&entered, 0, 0);
	sem_init(&filled, 0, 0);
	sem_init(&free_, 0, 0);

	pthread_t pass[numOfPassengers];
	pthread_t cars[numOfCars];

	struct identifier pass_arg[numOfPassengers];
	int ind=0;
	for(int i=0;i<numOfPassengers;i++){
		pass_arg[ind].id=i;		
		pthread_create(&pass[ind],NULL,passenger,(void*)&pass_arg[ind]);
		ind++;
	}

	struct identifier cars_arg[numOfCars];
	ind=0;
	for(int i=0;i<numOfCars;i++){
		cars_arg[ind].id=i;		
		pthread_create(&cars[ind],NULL,car,(void*)&cars_arg[ind]);
		ind++;
	}
	
	ind=0;
	for(int j=0;j<numOfPassengers;j++){
		pthread_join(pass[ind],NULL);
		ind++;			
	}
	ind=0;
	for(int j=0;j<numOfCars;j++){
		pthread_join(cars[ind],NULL);
		ind++;			
	}
	return 0;	
}
