#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "private.h"
#include "uthread.h"
#include "queue.h"

/* Globals */
queue_t ready_Q;
queue_t exited_Q;

typedef enum state
{
	running,
	ready,
	blocked,
	exited
} state_t;

struct uthread_tcb
{
	state_t state;
	void *stack;
	uthread_ctx_t *context;
};

struct uthread_tcb *uthread_current(void)
{
	/* TODO Phase 2/3 */
}

void uthread_yield(void)
{
	/* TODO Phase 2 */
	queue_enqueue(ready_Q, uthread_current());
	
	
}

void uthread_exit(void)
{
	/* TODO Phase 2 */
}

int uthread_create(uthread_func_t func, void *arg)
{
	// Make a new thread
	struct uthread_tcb *new_thread = malloc(sizeof(struct uthread_tcb));
	// Check for thread allocation failure
	if (new_thread == NULL)
		return -1;
	// Prep the thread
	new_thread->state = ready;
	new_thread->stack = uthread_ctx_alloc_stack();
	// Check for stack allocateion failure
	if (new_thread->stack == NULL)
		return -1;
	// Allocate the context
	new_thread->context = malloc(sizeof(uthread_ctx_t));
	if (new_thread->context == NULL)
		return -1;
	// ret = 0 if success, -1 if failure
	int ret = uthread_ctx_init(new_thread->context, new_thread->stack, func, arg);
	if (ret == -1)
		return -1;
	// Add thread to the ready_Q
	queue_enqueue(ready_Q, new_thread);
	return 0;
}

int uthread_run(bool preempt, uthread_func_t func, void *arg)
{
	// Preempt check
	if (preempt)
		preempt_start(preempt);
	
	// Initialize the ready_Q and exited_Q
	ready_Q = queue_create();
	exited_Q = queue_create();
	// Check for queue allocation failure
	if (ready_Q == NULL || exited_Q == NULL)
		return -1;

	// Create the main thread
	struct uthread_tcb *main_thread = malloc(sizeof(struct uthread_tcb));
	// Check for thread allocation failure
	if (main_thread == NULL)
		return -1;
	// Prep the thread
	main_thread->state = running;
	main_thread->stack = uthread_ctx_alloc_stack();
	main_thread->context = malloc(sizeof(uthread_ctx_t));
	// Check for allocation failures
	if (main_thread->state == NULL || main_thread->stack == NULL || main_thread->context == NULL)
		return -1;
	
	// Check for thread creation failure
	if (uthread_create(func, arg))
		return -1;
	
	// Handle Qs and execution
	while(1)
	{
		// Check for completed threads
		
		// Check if the ready_Q is empty
		if (queue_length(ready_Q) == 0)
			break;
		// Dequeue the next thread
		struct uthread_tcb *next_thread = queue_dequeue(ready_Q, NULL);
		// Check for dequeue failure
		if (next_thread == NULL)
			return -1;
		// Set the next thread to running
		next_thread->state = running;
		// Swap contexts
		uthread_ctx_switch(main_thread->context, next_thread->context);
		// Check if the thread has exited
		if (next_thread->state == exited)
		{
			// Free the stack and context
			uthread_ctx_destroy_stack(next_thread->stack);
			free(next_thread->context);
			// Add the thread to the exited_Q
			queue_enqueue(exited_Q, next_thread);
		}
		else
		{
			// Add the thread back to the ready_Q
			queue_enqueue(ready_Q, next_thread);
		}
		uthread_yield();
	}

	if(preempt)
		preempt_stop();
		
	return 0;
}

void uthread_block(void)
{
	/* TODO Phase 3 */
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 3 */
}
