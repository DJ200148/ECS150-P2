#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100

sigset_t x;
struct sigaction y;
struct itimerval z;

void preempt_disable(void)
{
	/* TODO Phase 4 */
	sigemptyset(&x);
	sigaddset(&x, SIGVTALRM);
	sigprocmask(SIG_BLOCK, &x, NULL);
}

void preempt_enable(void)
{
	/* TODO Phase 4 */
	/* Enable preemption by unblocking the SIGVTALRM signal */
	sigemptyset(&x);
	sigaddset(&x, SIGVTALRM);
	sigprocmask(SIG_UNBLOCK, &x, NULL);
}

void preempt_start(bool preempt)
{
	/* TODO Phase 4 */
	if (preempt) {
        /* Block signal temporarily */
        sigemptyset(&x);
        sigaddset(&x, SIGVTALRM);
        sigprocmask(SIG_BLOCK, &x, NULL);

        /* Install signal handler */
        y.sa_handler = &uthread_yield;
        sigemptyset(&y.sa_mask);
        y.sa_flags = 0;
        sigaction(SIGVTALRM, &y, NULL);

        /* Configure timer */
        z.it_value.tv_sec = 0;
        z.it_value.tv_usec = 1000000 / HZ;
        z.it_interval.tv_sec = 0;
        z.it_interval.tv_usec = 1000000 / HZ;
        setitimer(ITIMER_VIRTUAL, &z, NULL);

        /* Unblock signal */
        sigprocmask(SIG_UNBLOCK, &x, NULL);
    }
}

void preempt_stop(void)
{
	/* TODO Phase 4 */
	//restore configuration
	sigaction(SIGVTALRM, &old_action, NULL);
	setitimer(ITIMER_VIRTUAL, &old_itimerval, NULL);
}

