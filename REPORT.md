
Grading comment:
Excellent report

Report includes great details and insight about the submitted code and really helps understand the implementation even before reading it.

Report typically contains many paragraphs organized with a hierarchy of titles, addressing the different aspects of the implementation. Report includes the following items:

High-level description of implementation
Justification of design choices
Explanation of limitations
Proper file formatting
Markdown syntax
80 characters per line max
Correct spelling and grammar






What we got last time:

Grading comment:
Satisfactory report

Report suffers from a few important flaws. It typically contains a few, somewhat organized, paragraphs that mostly describes what the implementation does, but offers little insight about //how the implementation works and is organized.

-----------------------------------------------------------------

## Queue Implementation

Our queue is implemented using a linked list with two pointers, a head and a tail. The first element added to the list will be the first one out (FIFO). A linked list satisfied our time complexity restraints allowing us to create all of our functions (other than `queue_iterate()` and `queue_delete()`) in O(1) time. 

Elements can be added to the queue by first calling `queue_create()` to allocate memory, then, we can add elements by calling `queue_enqueue()` which will set the head pointer to the new node. Elements can be removed by using the `queue_dequeue()` function. This will remove the oldest item in the queue by setting the node's data pointer to its data. Calling `queue_delete()` will 



## Uthread Implementation

Our 'uthread' implementation relies on the four main functions uthread_create(), uthread_yield(), uthread_exit() and uthread_block().