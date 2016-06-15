#include "semaphore.h"

void
init(int max, struct Semaphore *s){
  s->hold = max;
	s->begin = 0;
	s->end = 0;
	lock_init(&s->lock);
}

void
sem_acquire(struct Semaphore *s){
	lock_acquire(&s->lock);
	//still have room just dec semaphore
	if (s->hold > 0){
		s->hold--;
		lock_release(&s->lock);
	}
	//full just sleep 
	//proc max is 63 cant overflow
	else{
	  int pid = getpid();
		//printf(1, "pid = %d\n", pid); 
		s->que[s->end] = pid;
		//move end over or loop back around
		if (s->end < 63)
			s->end++;
		else
			s->end = 0;
		lock_release(&s->lock);
		tsleep();
	}
}

void
sem_signal(struct Semaphore *s){
	lock_acquire(&s->lock);
	if (s->begin != s->end){
		//wake up the front of the queue
		//move front up one
		//or loop around to 0
		twakeup(s->que[s->begin]);
		if (s->begin < 63)
			s->begin++;
		else
			s->begin = 0;
		//add to semaphore
	}
	else{
		//printf(1, "adding hold\n");
		s->hold++;
	}
	lock_release(&s->lock);
}



