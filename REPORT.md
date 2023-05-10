# Project 2: User-Level Threads

## Queue Implementation

Our queue is implemented using a linked list with two pointers, a head and a 
tail. The first element added to the list will be the first one out (FIFO). A 
linked list satisfied our time complexity restraints allowing us to create all 
of our functions (other than `queue_iterate()` and `queue_delete()`) in O(1) 
time.

Elements can be added to the queue by first calling `queue_create()` to 
allocate memory, then, we can add elements by calling `queue_enqueue()` which 
will set the head pointer to the new node.

Elements can be removed by using the `queue_dequeue()` function. This will 
remove the oldest item in the queue by setting the node's data pointer to its 
data. `queue_delete()` will remove the node that contains the specified data 
from the queue. Finally, to destroy the queue we call `queue_destroy()` which 
will deallocate all the memory used in by the queue.

---
## Uthread Implementation

Our uthread library has two global queues, ready_Q and exited_Q, which hold 
threads that are ready to run and threads that have finished running. 
`curr_thread` keeps track of the currently running thread.

The `uthread_current()` function returns a pointer to the currently running 
thread. The `uthread_create()` function creates a new thread and adds it to the 
ready queue. The `uthread_yield()` function saves the current context and 
switches to the next ready thread in the queue. The `uthread_exit()` function 
marks the current thread as exited and switches to the next thread in the 
queue. The `uthread_block()` function sets the current thread's state to 
blocked and switches to the next thread in the queue. `uthread_unblock()` 
simply unblocks the specified thread.

---
## Semaphore Implementation

Our semaphore is implemented using a structure with two fields: count, an 
integer that represents the number of available resources, and blocked_Q, a 
queue that contains threads waiting for the semaphore. The implementation 
satisfies our time complexity constraints, allowing us to create all of our 
functions (other than `sem_destroy()`) in O(1) time.

A semaphore can be created by calling `sem_create()` function. This will 
allocate memory for the semaphore structure and initialize its fields with the 
specified count. If the allocation fails, it returns NULL.

To destroy a semaphore, we call `sem_destroy()`, which checks if the semaphore 
is valid and not being used by any thread. If other threads are blocked on the 
semaphore or if its invalid, `sem_destroy()` will return -1. Otherwise, the 
function will deallocate all memory used by the semaphore.

To take a semaphore, we call `sem_down()`. This first checks if the semaphore 
is valid. If its not, `sem_down()` will return -1. Otherwise, the function will 
attempt to decrement the semaphore's count. If the count is zero, the function 
will enqueue the calling thread onto the semaphore's waiting queue and block 
the thread. If the count is nonzero, the function will decrement the count.

To release a semaphore, we call `sem_up()`. This function first checks if the 
semaphore is valid. If it is not, `sem_up()` will return -1. Otherwise, the 
function increments the semaphore's count and checks if there are any threads 
waiting on the semaphore. If there are, the function dequeues the oldest thread 
from the semaphore's waiting queue and unblocks it by calling 
`uthread_unblock()`.

---
## Preemption Implementation

The preemption mechanism in the libuthread library uses a timer to force a 
context switch between threads. The frequency of the timer is set by HZ which 
is defined as 100 times per second.

When preemption is disabled using `preempt_disable()`, the SIGVTALRM signal is 
blocked. Conversely, enabling preemption using `preempt_enable()` unblocks the 
signal.

To enable preemption, `preempt_start()` sets up a timer to send the SIGVTALRM 
signal at a frequency of 100 Hz using `setitimer()`. A signal handler function 
`sighandler()` is also registered to handle the SIGVTALRM signal. The handler 
function calls `uthread_yield()` to force a context switch between threads.

To stop preemption, `preempt_stop()` restores the previous timer configuration 
using `setitimer()` and the previous signal handler function using 
`sigaction()`.

The `uthread_ctx_switch()` function is responsible for switching between two 
execution contexts. This function is used by the `uthread_yield()` function to 
force a context switch when preemption is enabled.

The `uthread_ctx_alloc_stack()` and `uthread_ctx_destroy_stack()` functions 
allocate and deallocate a stack segment respectively. These functions are used 
by `uthread_create()` to create new threads.

The `uthread_ctx_init()` function initializes a thread's execution context. 
This function is used by `uthread_create()` to initialize the execution context 
of new threads.

---
## Testing

### queue_tester.c

These tests are testing various functionalities of our queue data structure implementation. First we test that the queue is created successfully with `test_create()`. Next we test that we can add two items to the queue and then remove the first item to ensure that the first item added is also the first item removed (FIFO) with `test_FIFO()`. `test_queue_empty()` checks if a newly created queue is empty. `test_add_item()` adds an item to the queue and checks if the enqueue operation was successful. `test_addRemove_mult_items()` adds multiple items to the queue, then removes them all and ensures that the queue is empty. `test_queue_dequeue()` adds an item to the queue, removes it, and ensures that the dequeued item is the same as the one that was originally added.

### test_preempt.c

This is testing whether the uthread library can handle a timer interrupt signal (SIGINT) and switch to another thread correctly. The main thread creates a child thread that loops continuously and increments a counter variable `count`. The main thread also sets a timer and raises the SIGINT signal when the timer expires. The child thread handles the SIGINT signal and prints the final value of `count`. This tests the functionality of the uthread library to perform context switching and signal handling properly. The modification to the file adds a small delay in the child thread's loop to allow the `count` variable to increment before the signal is raised.

# TODO:
- Add a new test program in the apps directory, called test_preempt.c, which tests the preemption. Explain in your report why this program demonstrates that your preemptive scheduler works.
- Add a new test program in the apps directory, called queue_tester.c, which tests your queue implementation. It is important that your tester should be as comprehensive as possible in order to ensure that your queue implementation is resistant. It will ensure that you don’t encounter bugs when using your queue later on. Explain in your report why this program demonstrates that your queue implementation works.
- Read over the report and make sure it is complete and accurate. Make sure that you have answered all the questions in the report.

# Release Procedures
- Make a new branch off of master called `turnedin`
- Remove all unessesary files from the `turnedin`
- change the MAKEFILES and remove the -g flag use -p -Wall -Wextra -Werror
- Turn in the project on gradescope


## Items in the `turnedin` branch
- `uthread.c`
- `preemept.c`
- `queue.c`
- `sem.c`
- `AUTHORS`
- `REPORT.md`
- `libuthread/Makefile`
- `apps/queue_tester.c`
- `apps/test_preempt.c`