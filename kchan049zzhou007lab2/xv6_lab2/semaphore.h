#include "types.h"
#include "user.h"

struct Semaphore{
				int que[63];
				int hold;
				int begin;
				int end;
				lock_t lock;
};

void
init(int max, struct Semaphore *s);

void
sem_acquire(struct Semaphore *s);

void
sem_signal(struct Semaphore *s);
	
