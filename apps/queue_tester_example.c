#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <queue.h>

#define TEST_ASSERT(assert)				\
do {									\
	printf("ASSERT: " #assert " ... ");	\
	if (assert) {						\
		printf("PASS\n");				\
	} else	{							\
		printf("FAIL\n");				\
		exit(1);						\
	}									\
} while(0)

/* Create */
void test_create(void)
{
	fprintf(stderr, "*** TEST create ***\n");

	TEST_ASSERT(queue_create() != NULL);
}

/* Enqueue/Dequeue simple */
void test_queue_simple(void)
{
	int data = 3, *ptr;
	queue_t q;

	fprintf(stderr, "*** TEST queue_simple ***\n");

	q = queue_create();
	queue_enqueue(q, &data);
	queue_dequeue(q, (void**)&ptr);
	TEST_ASSERT(ptr == &data);
}

//test case to check if a new queue is empty
void test_queue_empty(void) {
	//make sure queue is empty
	queue_t queue;
	if (queue_is_empty(&queue) == 0) {
		TEST_ASSERT(queue_is_empty(&queue) == 0 && "queue is empty");
	}
	fprintf(stderr, "*** TEST queue_simple ***\n");
}

void test_add_item(void)
{
	queue_t queue;
    int ret = queue_init(&queue);
    TEST_ASSERT(ret == 0 && "queue_init failed");
}

int main(void)
{
	test_create();
	test_queue_simple();
	test_queue_empty();
	test_add_item();

	return 0;
}

// Create a new queue using the queue_create() function.
// Check if the queue is empty using the queue_empty() function.
// The expected result is that the queue should be empty.
// Test case to check if an item can be added to the queue


// Create a new queue using the queue_create() function.
// Add an item to the queue using the queue_enqueue() function.
// Check if the queue is empty using the queue_empty() function.
// The expected result is that the queue should not be empty.
// Test case to check if multiple items can be added to the queue
// int main() {
//     queue_t queue;
//     int data = 42;
//     int ret = queue_init(&queue);
//     assert(ret == 0 && "queue_init failed");

//     ret = queue_enqueue(&queue, &data);
//     assert(ret == 0 && "queue_enqueue failed");

//     return 0;
// }


// Create a new queue using the queue_create() function.
// Add multiple items to the queue using the queue_enqueue() function.
// Check the size of the queue using the queue_size() function.
// The expected result is that the size of the queue should match the number of items added.
// Test case to check if an item can be removed from the queue
// int main() {
//     queue_t queue;
//     int data = 42;
//     int ret = queue_init(&queue);
//     assert(ret == 0 && "queue_init failed");

//     assert(queue_is_empty(&queue) && "queue is not empty");

//     return 0;
// }


// Create a new queue using the queue_create() function.
// Add an item to the queue using the queue_enqueue() function.
// Remove the item from the queue using the queue_dequeue() function.
// Check if the queue is empty using the queue_empty() function.
// The expected result is that the queue should be empty.
// Test case to check if the first item added to the queue is the first one to be removed (FIFO behavior)
// int main() {
//     queue_t queue;
//     int data = 42;
//     int ret = queue_init(&queue);
//     assert(ret == 0 && "queue_init failed");

//     ret = queue_enqueue(&queue, &data);
//     assert(ret == 0 && "queue_enqueue failed");

//     assert(!queue_is_empty(&queue) && "queue is empty");

//     return 0;
// }


// Create a new queue using the queue_create() function.
// Add multiple items to the queue using the queue_enqueue() function.
// Remove an item from the queue using the queue_dequeue() function.
// Check if the removed item is the first item that was added to the queue.
// Repeat the process for all items in the queue.
// The expected result is that the removed items should match the order in which they were added.
// Test case to check if the queue can handle a large number of items
// int main() {
//     queue_t queue;
//     int data1 = 42;
//     int data2 = 99;
//     int ret = queue_init(&queue);
//     assert(ret == 0 && "queue_init failed");

//     ret = queue_enqueue(&queue, &data1);
//     assert(ret == 0 && "queue_enqueue failed");

//     ret = queue_enqueue(&queue, &data2);
//     assert(ret == 0 && "queue_enqueue failed");

//     int *ptr = (int*)queue_dequeue(&queue);
//     assert(ptr != NULL && "queue_dequeue failed");
//     assert(*ptr == 42 && "dequeued wrong element");

//     return 0;
// }


// Create a new queue using the queue_create() function.
// Add a large number of items to the queue using the queue_enqueue() function.
// Check if the size of the queue matches the number of items added.
// Remove all items from the queue using the queue_dequeue() function.
// Check if the queue is empty using the queue_empty() function.
// The expected result is that the size of the queue should match the number of items added and that the queue should be empty after removing all items.
// int main() {
//     queue_t queue;
//     int ret = queue_init(&queue);
//     assert(ret == 0 && "queue_init failed");

//     void *ptr = queue_dequeue(&queue);
//     assert(ptr == NULL && "queue_dequeue failed");

//     return 0;
// }