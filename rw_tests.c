#include <stdio.h>
#include <pthread.h>

#include "pipe_sem.h"

int sharedValue;
int readcount = 0;
int writecount = 0;
int waitingReaders = 0;
int waitingWriters = 0;
pipe_sem_t readingsem;
pipe_sem_t writingsem;
pipe_sem_t mutex;

// Used pseudocode from notes and Wikipedia for the reader and the writer
void reader(void *f)
{
	// Wait on mutex
    pipe_sem_wait(&mutex);

    if(writecount + waitingWriters > 0)
    {
        waitingReaders++;
    }
	else
    {
		// Signal readingsem
        pipe_sem_signal(&readingsem);
        readcount++;
    }

	// Signal mutex
    pipe_sem_signal(&mutex);

	// Wait on readingsem
    pipe_sem_wait(&readingsem);
    accessValueRead();

	// Wait on mutex
    pipe_sem_wait(&mutex);

    // Decrease reader count
	readcount--;

    if(readcount == 0 && waitingWriters > 0)
    {
		// Signal writingsem
        pipe_sem_signal(&writingsem);
        writecount--;
        waitingReaders++;
    }

	// Signal mutex
    pipe_sem_signal(&mutex);

    pthread_exit(NULL);
}
    
void writer(void *f)
{
	// Wait on mutex
    pipe_sem_wait(&mutex);

    if(writecount + readcount > 0)
	{
        waitingWriters++;
	}
    else
    {
		// Signal writingsem
        pipe_sem_signal(&writingsem);
        writecount++;
    }

	// Signal mutex
    pipe_sem_signal(&mutex);

	// Wait on writingsem
    pipe_sem_wait(&writingsem);
    accessValueWrite();

	// Wait on mutex
    pipe_sem_wait(&mutex);

	// Decrease writer count
    writecount--;

    if(waitingWriters > 0)
    {
		// Signal writingsem
        pipe_sem_signal(&writingsem);
        writecount++;
        waitingWriters--;
    }
    else if(waitingReaders > 0)
    {
		// Signal readingsem
        pipe_sem_signal(&readingsem);

        readcount++;
        waitingReaders--;
    }

	// Signal mutex
    pipe_sem_signal(&mutex);

    pthread_exit(NULL);
}

/*
 *	When a thread is allowed to access
 *	the resource (i.e., enter its CS), it first outputs a message:
 *
 *	Reader thread <id> enters CS
 *	or
 *	Writer thread <id> enters CS
 *
 *	Then, it calls
 *	sleep(1);
 *	to simulate the time elapse for its access. Finally, it outputs:
 *
 *	Reader thread <id> is exiting CS
 *	or
 *	Writer thread <id> is exiting CS. Then the thread ends.
 */
void accessValueRead()
{
    printf("Reader thread %d enters CS\n", pthread_self());
    sleep(1);
    printf("Reader thread %d is exiting CS\n", pthread_self());
}

void accessValueWrite()
{
    printf("Writer thread %d enters CS\n", pthread_self());
    sleep(1);
    printf("Writer thread %d is exiting CS\n", pthread_self());  
}

int main(int argc, char** argv)
{
	// Making the semaphores for reading, writing, and mutex.
    pipe_sem_init(&readingsem, 0);
    pipe_sem_init(&writingsem, 0);
    pipe_sem_init(&mutex, 1);

    int thread_count = argv[1];
    int interval = atoi(argv[argc-1]);
	int i;

    for(i = 2; i < argc - 1; ++i)
    {
        pthread_t thread;
        if (strcmp(argv[i], "0") == 0)
		{
            pthread_create(&thread, NULL, reader, 0);
		}
        else
		{
            pthread_create(&thread, NULL, writer, 0);
		}
        sleep(interval);
    }

    pthread_exit(0);
}

