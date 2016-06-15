#include "semaphore.h"

void monkey(void* daddy);
void dommonkey(void* daddy);
int random(int max);

struct Semaphore onemonkey;
struct Semaphore semamonkey;
struct Semaphore climb;
struct Semaphore lock1;
struct Semaphore lock2;
struct Semaphore lock3;
struct Semaphore tree;
int coconut = 0;
int nummonkeys = 0;
int movingup;
int movingdown;
int numdommonkeys = 0;
int isdom;
unsigned long rands = 1;

int r;
int rand() {
	r = r * 48053245 + 3480950;
	return r;
}
int main()
{
	r = 3;
  movingup = 0;
	movingdown = 0;
	isdom = 0;
	coconut = 0;
	init(1, &lock1);
	init(1, &lock2);
	init(1, &lock3);
	init(1, &climb);
	init(1, &onemonkey);
	init(1, &semamonkey);
	init(3, &tree);
  
	printf(1, "simple test case\n");
	thread_create(monkey,0);
	thread_create(monkey,0);
	thread_create(monkey,0);
	thread_create(dommonkey, 0);
	thread_create(monkey, 0);
	thread_create(monkey, 0);

	while(wait() >= 0);
	coconut = 0;
	printf(1, "random\n");
	//random case
	int i;
	for (i = 0; i < 15; i++){
			if (rand()%2 == 0)
					thread_create(monkey, 0);
			else
					thread_create(dommonkey, 0);
	}
	while(wait()>=0);
	
	printf(1, "edge\n");
	coconut = 0;

	thread_create(dommonkey, 0);
	thread_create(dommonkey, 0);
	thread_create(dommonkey, 0);
	thread_create(monkey, 0);
	thread_create(dommonkey, 0);
/*	printf(1, "random test case\n");
	int i; 
	for(i = 0; i < 37; i++){
	  if(random(4))
		  thread_create(monkey, 0);
		else
			thread_create(dommonkey, 0);
	}
	while(wait()>=0);	
*/
	while(wait() >= 0);

	exit();
	return 0;			
}


int random(int max){
	rands = rands * 166425+ 1013904233;
	return (int)(rands % max);
}



void monkey(void* daddy)
{
	nummonkeys++;
	sem_acquire(&onemonkey);
	sem_acquire(&semamonkey);
	sem_acquire(&tree);
	nummonkeys = nummonkeys - 1;
	sem_acquire(&lock1);
  movingup++;
	if(movingup == 1)
		sem_acquire(&climb);
	sem_signal(&lock1);
	sem_signal(&semamonkey);
	sem_signal(&onemonkey);
  //climbing up
  sem_acquire(&lock1);
	movingup = movingup - 1;
  if(movingup == 0)
	  sem_signal(&climb);
	sem_signal(&lock1);
	//get coconut
	coconut++;
	printf(1, "Monkey stealing coconut :]\n Monkeys Waiting: %d\n Dom Monkeys Waiting: %d \n", nummonkeys, numdommonkeys);
	sem_acquire(&lock2);
	movingdown++;
	if( movingdown == 1)
	  sem_acquire(&climb);
	sem_signal(&lock2);
	//climb down
	sem_acquire(&lock2);
	movingdown = movingdown - 1;
	if( movingdown == 0)
	  sem_signal(&climb);
	sem_signal(&lock2);
	sem_signal(&tree);
	texit();
}

void dommonkey(void* daddy)
{
  numdommonkeys++;
	sem_acquire(&lock3); 
	isdom++;
	if( isdom == 1)
	  sem_acquire(&semamonkey);
	sem_signal(&lock3);
	sem_acquire(&tree);
	numdommonkeys = numdommonkeys - 1;
	sem_acquire(&lock1);
	movingup++;
	if( movingup == 1)
	  sem_acquire(&climb);
	sem_signal(&lock1);
	//climb up
	sem_acquire(&lock1);
	movingup = movingup - 1;
	if( movingup == 0)
	  sem_signal(&climb);
	sem_signal(&lock1);
	//get coconut
	coconut++;
	printf(1, "Monkey stealing coconut :]\n Monkeys Waiting: %d\n Dom Monkeys waiting: %d \n", nummonkeys, numdommonkeys);
	sem_acquire(&lock2);
	movingdown++;
	if( movingdown == 1)
		sem_acquire(&climb);
	sem_signal(&lock2);
	//climb down
	sem_acquire(&lock2);
	movingdown = movingdown - 1;
	if( movingdown == 0)
	  sem_signal(&climb);
	sem_signal(&lock2);
	sem_signal(&tree);
	sem_acquire(&lock3);
	isdom = isdom - 1;
	if(isdom == 0)
	  sem_signal(&semamonkey);
	sem_signal(&lock3);
	texit();
}

