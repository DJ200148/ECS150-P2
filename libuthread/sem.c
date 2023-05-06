#include <stddef.h>
#include <stdlib.h>

#include "queue.h"
#include "sem.h"
#include "private.h"

struct semaphore {
	size_t count;
	queue_t blocked_Q;
};

sem_t sem_create(size_t count)
{
	// Allocate a new sem
	sem_t new_sem = malloc(sizeof(sem_t));
	if(new_sem == NULL)
		return NULL;
	// Initialize sem
	new_sem->count = count;
	new_sem->blocked_Q = queue_create();
	// Check if Q was created sucefully
	if(new_sem->blocked_Q == NULL)
	{
		free(new_sem);
		return NULL;
	}
	
	return &new_sem;
}

int sem_destroy(sem_t sem)
{
	// Check for invalid inputs
	if(!sem || queue_length(sem->blocked_Q) != 0)
		return -1;
	// Deallocate memory
	queue_destroy(sem->blocked_Q);
	free(sem);

	return 0;
}

int sem_down(sem_t sem)
{
	/* TODO Phase 3 */
	if (!sem)
		return -1;
	
	return 0;
}

int sem_up(sem_t sem)
{
	/* TODO Phase 3 */
	if (!sem)
		return -1;

	return 0;
}

