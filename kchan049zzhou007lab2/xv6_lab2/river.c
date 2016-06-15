#include "semaphore.h"

struct Semaphore can;
struct Semaphore miss;
struct Semaphore lock;
int nummiss;
int numcan;
unsigned long rands = 0;

void missarrive(void* daddy);
void canarrive(void* daddy);
int random(int);

int main(){
	nummiss = 0;
	numcan = 0;
	init(1, &lock);
	printf(1, "basic test case");
	thread_create(canarrive,0);
	thread_create(missarrive,0);
	thread_create(missarrive,0);
	while(wait()>= 0);
  printf(1, "\ncannibals: %d and missionaries: %d\n\n", numcan, nummiss);

	
	printf(1, "edge case shouldn't cross the river");	
	
	thread_create(canarrive,0);
	thread_create(canarrive,0);
	thread_create(missarrive,0);
	while(wait()>=0);
	printf(1, "\ncannibals: %d and missionaries: %d\n\n", numcan, nummiss);

	
	printf(1, "random test cases that should print out 12 row boats with 0 missionaries and 0 cannibals or else should print out less than 12 rowboats with 2 cannibals and 1 missionary as result");
	int i;
	for( i = 0; i < 33; i++)
	{
	  if(random(2))
		  thread_create(missarrive, 0);
		else 
			thread_create(canarrive, 0);
	}


	while(wait()>=0);
	printf(1, "\ncannibals: %d and missionaries: %d\n", numcan, nummiss);
	exit();
	return 0;
}

int random(int max){
	rands = rands * 166425+ 1013904233;
	return (int)(rands % max);
}

void missarrive(void* daddy) { 
	sem_acquire(&lock);
  nummiss++;
	if(nummiss == 3 || (numcan > 0 && nummiss == 2)){
	  sem_signal(&can);
		sem_signal(&can);
		printf(1, "\nRow Boat");
		if (nummiss == 3){
		  printf(1, " with 3 missionaries");
			nummiss = 0;
		}
		else if(numcan == 3){
			printf(1, " with 3 cannibals");
			numcan = 0;
		}
		else{
			printf(1, " with 1 cannibal 2 missionaries");
			numcan = numcan - 1;
			nummiss = nummiss -2;
		}

	}
	sem_signal(&lock);
	texit();
}
	

	
void canarrive(void* daddy) { 
	sem_acquire(&lock);
  numcan++;
	if(numcan == 3 || (numcan > 0 && nummiss == 2)){
	  sem_signal(&can);
		sem_signal(&can);
		printf(1, "\nRow Boat");
		if (nummiss == 3){
		  printf(1, " with 3 missionaries");
			nummiss = 0;
		}
		else if(numcan == 3){
			printf(1, " with 3 cannibals");
			numcan = 0;
		}
		else{
			printf(1, " with 1 cannibal 2 missionaries");
			numcan = numcan - 1;
			nummiss = nummiss -2;
		}

	}
	sem_signal(&lock);
	texit();
}
	
