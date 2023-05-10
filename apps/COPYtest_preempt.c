#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "uthread.h"
#include "private.h"


void thread1(void* arg)
{
    (void) arg;
    printf("context switch happened\n");
}

void thread2(void* arg)
{
    (void) arg;
    printf("You switched to me as well\n");
    raise(SIGINT);
}

void thread(void* arg)
{
    (void) arg;
    uthread_create(thread1, NULL);
    uthread_create(thread2, NULL);
    while (1) {}  // if program doesn't terminate due to SIGINT, then it means there is error in our implmentation
}

int main(void)
{
	uthread_run(true, thread, NULL);
	return 0;
}