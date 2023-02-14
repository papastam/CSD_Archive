//Xristos Papastamos csd4569
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>
#include <time.h>

//Directions: 0:East, 1:West
int dir=0;
int carsonroad=0;
int carswaiting=0;

struct timespec t1;
struct timespec t2;

void *carFromEast(void *num);
void *carFromWest(void *num);

sem_t allowedCars;//semaphore maxing on 3 to count the number of cars on the road
sem_t cntchange;//binary semaphore to allow a thread to change carsonroad
sem_t dirchange;//binary semaphore to allow a thread to change dir

int main(int argc, char const *argv[]){
	srand(time(0));
	if(argc!=3 || strcmp(argv[1],"-c") || atoi(argv[2])<0){
		printf("Invalid syntax, please use \"./nr -c [num of cars]\"\n");
		return 0;
	}

	int i=0;
	int requestedCars=atoi(argv[2]);
	int carDirections[requestedCars];
	pthread_t threadarr[requestedCars];

	sem_init(&allowedCars, 0, 3);
	sem_init(&cntchange, 0, 1);
	sem_init(&dirchange, 0, 1);

	for(i=0;i<requestedCars;i++){

		int *arg = malloc(sizeof(*arg));
		*arg = i;

		carDirections[i]=rand()%2;
		if(carDirections[i]){
			pthread_create(&threadarr[i],NULL,carFromWest,arg);
		}else{
			pthread_create(&threadarr[i],NULL,carFromEast,arg);
		}
	}

	for(i=0;i<requestedCars;i++){
		pthread_join(threadarr[i],NULL);
	}
	printf("Exiting [carsonroad:%d][dir:%d]\n",carsonroad,dir);
	return 0;
}


void *carFromEast(void *num){

	t1.tv_sec  = 0;
	t1.tv_nsec = 10000000000L;
	
	int i=*((int *)(num));
	printf("(|) Car %d: Waiting to pass to East. [carsonroad:%d][dir:%d]\n",i,carsonroad,dir);	


	sem_wait(&allowedCars);
	if(dir==0){//if dir west
		sem_wait(&dirchange);
		dir=1;
		printf("(%%) Car %d changed direction to East [carsonroad:%d][dir:%d]\n",i,carsonroad,dir);
		sem_post(&dirchange);
	}

	sem_wait(&dirchange);
	sem_wait(&cntchange);
	carsonroad++;
	printf("(-) Car %d: Coming from East. [carsonroad:%d][dir:%d]\n",i,carsonroad,dir);
	sem_post(&cntchange);

	nanosleep(&t1, &t2);
	
	sem_wait(&cntchange);
	carsonroad--;
	sem_post(&cntchange);

	sem_post(&allowedCars);
	sem_post(&dirchange);

	printf("(#) Car %d: Reached to East. [carsonroad:%d][dir:%d]\n",i,carsonroad,dir);

	pthread_exit( NULL );
}

void *carFromWest(void *num){

	t1.tv_sec  = 0;
	t1.tv_nsec = 10000000000L;

	int i=*((int *)(num));
	printf("(|) Car %d: Waiting to pass to West. [carsonroad:%d][dir:%d]\n",i,carsonroad,dir);	

	sem_wait(&allowedCars);
	if(dir==1){//if dir east
		// while(carsonroad!=0){}
		sem_wait(&dirchange);
		dir=0;
		printf("(%%) Car %d changed direction to West [carsonroad:%d][dir:%d]\n",i,carsonroad,dir);
		sem_post(&dirchange);
	}
	
	sem_wait(&dirchange);
	sem_wait(&cntchange);
	carsonroad++;
	printf("(-) Car %d: Coming from West. [carsonroad:%d][dir:%d]\n",i,carsonroad,dir);
	sem_post(&cntchange);

	nanosleep(&t1, &t2);
	
	sem_wait(&cntchange);
	carsonroad--;
	sem_post(&cntchange);

	sem_post(&allowedCars);
	sem_post(&dirchange);

	printf("(#) Car %d: Reached to West. [carsonroad:%d][dir:%d]\n",i,carsonroad,dir);

	pthread_exit( NULL );
}