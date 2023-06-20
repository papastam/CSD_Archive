//Xristos Papastamos csd4569
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>


void *incomingCar(void *num);
void *ferry(void *num);

int carsBoarded=0;
int remainingCars=0;

sem_t carSlots;//semaphore maxing on 20 to count the number of cars on the ferry
pthread_mutex_t disembarkBarrier;
pthread_mutex_t boardBarrier;
pthread_mutex_t ferryRoute;

int main(int argc, char const *argv[]){
	
	srand(time(0));
	if(argc!=3 || strcmp(argv[1],"-c") || atoi(argv[2])<0){
		printf("Invalid syntax, please use \"./ferry -c [num of cars]\"\n");
		return 0;
	}

	int i=0;
	int carsRequested=atoi(argv[2]);
	remainingCars=carsRequested;
	int ferriesNeeded=ceil(carsRequested/20.0);
	pthread_t carsarr[carsRequested];
	pthread_t ferriesarr[ferriesNeeded];

	pthread_mutex_init (&boardBarrier, NULL);
	pthread_mutex_init (&disembarkBarrier, NULL);
	pthread_mutex_init (&ferryRoute, NULL);

	sem_init(&carSlots, 0, 20);

	pthread_mutex_lock(&ferryRoute);
	int j=0;
	int *test=malloc(sizeof(*test));
	*test = j;
	pthread_create(&ferriesarr[0],NULL,ferry,test);

	for(i=0;i<carsRequested;i++){
		int *arg = malloc(sizeof(*arg));
		*arg = i;

		pthread_create(&carsarr[i],NULL,incomingCar,arg);
	}

	for(i=1;i<ferriesNeeded;i++){
		int *arg = malloc(sizeof(*arg));
		*arg = i;

		pthread_mutex_lock(&ferryRoute);
		pthread_create(&ferriesarr[i],NULL,ferry,arg);
	}

	for(i=0;i<carsRequested;i++){
		if(i<ferriesNeeded){pthread_join(ferriesarr[i],NULL);}
		pthread_join(carsarr[i],NULL);
	}

	printf("EXITING [carsBoarded:%d]\n",carsBoarded);
	return 0;
}

void* incomingCar(void *num){
	unsigned int sleeptime=rand()%10;
	sleep(sleeptime);
	int i=*((int *)(num));

	printf("(*) Car %d arrived at the port [carsBoarded:%d]\n",i,carsBoarded);
	sem_wait(&carSlots);
	// printf("car slots ok");
	while(pthread_mutex_trylock(&boardBarrier)){}
	carsBoarded++;
	printf("(^) Car %d boarding on the ferry [carsBoarded:%d]\n",i,carsBoarded);
	pthread_mutex_unlock(&boardBarrier);

	while(pthread_mutex_trylock(&disembarkBarrier)){}
	carsBoarded--;
	printf("(\\) Car %d disembarking the ferry [carsBoarded:%d]\n",i,carsBoarded);
	pthread_mutex_unlock(&disembarkBarrier);

	sem_post(&carSlots);
	pthread_exit( NULL );
}

void* ferry(void *num){
	int i=*((int *)(num));

	printf("\n( [ )Ferry %d starts the boarding process [carsBoarded:%d]\n\n",i,carsBoarded);
	pthread_mutex_lock(&disembarkBarrier); 
	pthread_mutex_unlock(&boardBarrier);

	if(remainingCars<20){
		while(carsBoarded<remainingCars){}
	}else{
		while(carsBoarded<20){}
	}

	printf("\n( - )Ferry %d departed [carsBoarded:%d]\n\n",i,carsBoarded);
	pthread_mutex_lock(&boardBarrier);
	sleep(5);

	printf("\n( ] )Ferry %d disembarks [carsBoarded:%d]\n\n",i,carsBoarded);
	pthread_mutex_unlock(&disembarkBarrier);

	remainingCars-=20;//this variable doesnt need to be in a critical section since ferries are never executed in paralell

	sleep(3);
	pthread_mutex_unlock(&ferryRoute);
	pthread_exit( NULL );
}