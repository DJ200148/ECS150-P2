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
struct uthread_tcb *current_thread;
struct uthread_tcb *idle_thread;

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
	queue_t blocked_Q;
};

struct uthread_tcb *uthread_current(void)
{
	return current_thread;
}

void uthread_yield(void)
{

	struct uthread_tcb *next_thread;
	
	struct uthread_tcb *current = uthread_current();
	// Put the current thread back on the queue and get the next thread
	queue_enqueue(ready_Q, current);
	queue_dequeue(ready_Q, (void**)&next_thread);
	
	if (next_thread == NULL)
		perror("queue_dequeue");
	
	if(current != next_thread)
	{
		// Prep thread
		current_thread->state = ready;
		next_thread->state = running;
		current_thread = next_thread;

		// Swap contexts
		uthread_ctx_switch(current->context, next_thread->context);
	}
}

void uthread_exit(void)
{
	// Set the current thread to exited and remove it
	current_thread->state = exited;
	uthread_ctx_destroy_stack(current_thread->stack);
	queue_enqueue(exited_Q, uthread_current());
	// yield to the next thread
	struct uthread_tcb *next_thread;
	queue_dequeue(ready_Q, (void**)&next_thread);
	struct uthread_tcb* curr = current_thread;
	
	current_thread = next_thread;
	current_thread->state = running;
	uthread_ctx_switch(curr->context, next_thread->context);
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
	//Preempt check
	// if (preempt)
	// 	preempt_start(preempt);
	(void)preempt;
	// Initialize the ready_Q and exited_Q
	ready_Q = queue_create();
	exited_Q = queue_create();
	// Check for queue allocation failure
	if (ready_Q == NULL || exited_Q == NULL)
		return -1;

	// Create the main thread
	idle_thread = malloc(sizeof(struct uthread_tcb));
	// Check for thread allocation failure
	if (idle_thread == NULL)
		return -1;
	// Prep the thread
	idle_thread->state = running;
	//idle_thread->stack = uthread_ctx_alloc_stack();
	idle_thread->context = malloc(sizeof(uthread_ctx_t));

	//Check for allocation failures
	if (idle_thread->state != running || idle_thread->context == NULL)
		return -1;

	// Make the idle thread the first thread we "run"
	current_thread = idle_thread;
	
	// Check for thread creation failure
	if (uthread_create(func, arg))
		return -1;
	
	// Handle Qs and execution
	while(1)
	{
		// Check for completed threads
		while(queue_length(exited_Q) > 0){
			// Deallocate the dead threads
			struct uthread_tcb *exited_thread;
			queue_dequeue(exited_Q, (void**)&exited_thread);
			free(exited_thread);
		}

		// Check if all the threads are completed
		if(queue_length(ready_Q) <= 0)
			break;		
		
		uthread_yield();
	}

	// if(preempt)
	// 	preempt_stop();
		
	return 0;
}

void uthread_block(void)
{
	/* TODO Phase 3 */
	uthread_current()->state = blocked;
	struct uthread_tcb *current = uthread_current();
	
	// Remove the current thread from the ready queue
	queue_delete(ready_Q, current);
	
	// Add the current thread to the blocked queue
	queue_enqueue(current->blocked_Q, current);
	
	// Yield to the next thread
	uthread_yield();
}

void uthread_unblock(struct uthread_tcb *uthread)
{
	/* TODO Phase 3 */
	if (uthread == NULL || uthread->state != blocked)
		return;

	uthread->state = ready;
	queue_enqueue(ready_Q, uthread);
}
