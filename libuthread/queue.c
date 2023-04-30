#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

// Notes:
// Used linked list for the base of the FIFO queue
// Have an address in the queue_t
// makefile

struct node {
	void * data;
	struct node * next;
};

struct queue {
	/* TODO Phase 1 */
	struct node * head;
	struct node * tail;
	int length;
};

// Dillon O(1)
queue_t queue_create(void)
{
	/* TODO Phase 1 */
}

// Hayden O(1)
int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */
}

// Dillon O(1)
int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */
}

// Dillon O(1)
int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */
}
// Hayden NOT O(1)
int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	//parse linked list
	//if data is found, delete it
}

// Together NOT O(1)
int queue_iterate(queue_t queue, queue_func_t func)
{
	/* TODO Phase 1 */
}

// Hayden O(1)
int queue_length(queue_t queue)
{
	/* TODO Phase 1 */
	//return queue->length;
}

