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
static sigset_t x;
static struct sigaction y;
static struct itimerval z;


void preempt_disable(void)
{
	/* TODO Phase 4 */
	sigprocmask(SIG_BLOCK, &x, NULL);
}

void preempt_enable(void)
{
	/* TODO Phase 4 */
}

void preempt_start(bool preempt)
{
	/* TODO Phase 4 */
	(void) preempt;
}

void preempt_stop(void)
{
	/* TODO Phase 4 */
}

