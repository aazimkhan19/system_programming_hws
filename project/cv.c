#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
int numOfPassengers = 4;
int numOfCars = 1;
int waitTime = 5000;
int runTime = 60;
int numOfSeats = 2;
struct identifier{
	 int id;
};

pthread_mutex_t available;
pthread_mutex_t entered;
pthread_mutex_t filled;
pthread_mutex_t free_;

void* passenger (void *p) {
  	srand(time(0));
  	struct identifier *ind = (struct identifier*)p;
  	int ID = ind->id;
  	while (1) {
			 	for(int i = 0; i < (0xFFFFFFFF); i++); //Sleep
				pthread_mutex_unlock(&available);
				printf("%d taken\n", ID);
				pthread_mutex_lock(&entered);
				printf("%d inside\n", ID);
				printf("passenger %d is running\n", ID);
				pthread_mutex_unlock(&filled);
				printf("passenger %d is free\n", ID);
				pthread_mutex_unlock(&free_);

  	}
}

void* car (void *p) {
    srand(time(0));
	  struct identifier *ind = (struct identifier*)p;
	  int ID = ind->id;
	  while (1) {
		    printf("car %d loading\n", ID);
        for (int i = 0; i < numOfSeats; i++) {
            //signals(&available, "ready");
            pthread_mutex_lock(&available);
						printf("car %d ready\n", ID);
        }
        for (int i = 0; i < numOfSeats; i++) {
            pthread_mutex_unlock(&entered);
						printf("car %d OK\n", ID);
        }
        for (int i = 0; i < numOfSeats; i++) {
            //signals(&filled, "reserved");
            pthread_mutex_lock(&filled);
						printf("car %d filled\n", ID);
        }
        printf("car %d is running\n", ID);
        for(int i = 0; i < (0xFFFFFFFF); i++); //Sleep
        printf("car %d unloading\n", ID);
				for(int i = 0; i < numOfSeats; i++){
						printf("opened %d\n", ID);
            			pthread_mutex_lock(&free_);
				}
    }
}

int main(void)
{
    int error;
    pthread_t pass[numOfPassengers];
    pthread_t cars[numOfCars];


    if (pthread_mutex_init(&available, NULL) != 0 ||
				pthread_mutex_init(&entered, NULL) != 0 ||
		 		pthread_mutex_init(&filled, NULL) != 0 ||
				pthread_mutex_init(&free_, NULL) != 0)
		{
        printf("\n mutex init has failed\n");
        return 1;
    }

    struct identifier pass_arg[numOfPassengers];
    int ind = 0;
    for(int i = 0; i < numOfPassengers; i++){
    		pass_arg[ind].id = i;
    		pthread_create(&pass[ind], NULL, passenger, (void*)&pass_arg[ind]);
        if (error != 0)
            printf("\nThread can't be created :[%s]", strerror(error));
    		ind++;
  	}

    struct identifier cars_arg[numOfCars];
    ind = 0;
    for (int i = 0; i < numOfCars; i++) {
        cars_arg[ind].id = i;
        pthread_create(&cars[ind], NULL, car, (void*)&cars_arg[ind]);
        if (error != 0)
            printf("\nThread can't be created :[%s]", strerror(error));
        ind++;
    }

    for(int i = 0; i < numOfPassengers; i++) {
        pthread_join(pass[i], NULL);
    }
    for(int i = 0; i < numOfCars; i++) {
        pthread_join(cars[i], NULL);
    }

    pthread_mutex_destroy(&available);
    pthread_mutex_destroy(&entered);
		pthread_mutex_destroy(&filled);
    pthread_mutex_destroy(&free_);


    return 0;
}
