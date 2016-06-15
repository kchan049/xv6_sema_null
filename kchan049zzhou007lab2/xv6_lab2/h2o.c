#include "semaphore.h"
struct Semaphore h;
struct Semaphore o;
struct Semaphore lock;
int water = 0;

void oReady(void* daddy);
void hReady(void* daddy);

int main(){
	init(0, &o);
	init(0, &h);
	init(1, &lock);
	int i;

	printf(1, "complex\n");
	for(i = 0; i < 30; i++)
	{
	  if(i%3 == 0)
		  thread_create(oReady, 0);
		else
		  thread_create(hReady, 0);
	}
	
 	while(wait()>=0);
	
	printf(1, "simple\n");
	thread_create(hReady, 0);
	thread_create(oReady, 0);
	thread_create(hReady, 0);

 	while(wait()>=0);

	printf(1, "edge\n");
	thread_create(hReady, 0);
	thread_create(hReady, 0);
	thread_create(hReady, 0);
	thread_create(hReady, 0);
	thread_create(oReady, 0);
	thread_create(oReady, 0);
 	
	while(wait()>=0);

	exit();
	return 0;
}

void hReady(void* daddy) { 
	sem_signal(&h);
	sem_acquire(&o);
	texit();
} 
void oReady(void* daddy){
	sem_acquire(&h);
	sem_acquire(&h);
	sem_signal(&o);
	sem_signal(&o);
	sem_acquire(&lock);
	printf(1, "make  water\n");
	water++;
	sem_signal(&lock);
	texit();
}
