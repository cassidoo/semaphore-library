#ifndef __CASSIDOO_PIPE_SEM__
#define __CASSIDOO_PIPE_SEM__

typedef struct{
    int semInfo[2];
} pipe_sem_t;

/*
 * Initialize a semaphore and set its initial value.
 */
void pipe_sem_init(pipe_sem_t*, int);

/*
 * Perform a wait operation on the semaphore.
 */
void pipe_sem_wait(pipe_sem_t*);

/*
 * Perform a signal operation on the semaphore.
 */
void pipe_sem_signal(pipe_sem_t*);

/*
 * Stops any of the waiting of any residual processes/threads
 * then unallocates all resources associated with this semaphore.
 */
//void pipe_sem_destroy(pipe_sem_t*);

#endif


