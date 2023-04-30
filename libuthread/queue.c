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
	queue_t queue = malloc(sizeof(struct queue));

	// Check if malloc failed
	if(queue == NULL)
		return NULL;
	// Else, initialize queue
	queue->head = NULL;
	queue->tail = NULL;
	queue->length = 0;
	return queue;
}

// Hayden O(1)
int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */
}

// Dillon O(1)
int queue_enqueue(queue_t queue, void *data)
{
	// Check for valid inputs
	if (queue == NULL || data == NULL)
		return -1;
	
	// Create new node
	struct node * newNode = malloc(sizeof(struct node));
	if (newNode == NULL)
		return -1;
	
	// Initialize new node
	newNode->data = data;
	newNode->next = NULL;
	
	// Add new node to queue
	if(queue->head == NULL)
		queue->head = newNode;
	queue->tail = newNode;
	queue->length++;

	return 0;
}

// Dillon O(1)
int queue_dequeue(queue_t queue, void **data)
{
	// Check for valid inputs
	if (queue == NULL || data == NULL || queue->head == NULL || queue->tail == NULL || queue->length == 0)
		return -1;
	
	// Set head data from queue to data
	*data = queue->head->data;

	// Remove head from queue and update the queue
	struct node * temp = queue->head;
	queue->head = queue->head->next;
	queue->length--;
	free(temp);

	if (queue->length == 0)
		queue->tail = NULL;
	
	return 0;
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

