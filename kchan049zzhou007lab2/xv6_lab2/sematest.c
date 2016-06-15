#include "semaphore.h"
struct Semaphore s;
int num = 0;

void test(void*z);

int main() {
	init(1, &s);

	int i;
	for (i = 0; i < 50; i++) {
		int* pid = thread_create(test, 0);
		if(pid <= 0){
       printf(1,"wrong happen");
       exit();
   	} 
   }
	while(wait()>= 0)
  printf(1,"\nback to parent");
	exit();
	return 0;
}

void test(void* z) {
	sem_acquire(&s);
	int i;
	for (i = 0; i < 60; i++);
	printf(1, "%d\n", num);
	num++;
	sem_signal(&s);
	texit();
}



