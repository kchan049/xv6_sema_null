#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

void testyield(void *arg) {
	thread_yield();
	printf(1, "yield\n");
	texit();
}
void run(void *arg) {
	printf(1, "run\n");
	texit();
}


int main(void) {
	
	thread_create(testyield, 0);
	thread_create(run, 0);
	thread_create(testyield, 0);
	thread_create(run, 0);
	
	while(wait() >= 0);
	exit();
	return 0;
}
