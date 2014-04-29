#include "pipe_sem.h"
#include <stdlib.h>
#include <stdio.h>

void pipe_sem_init(pipe_sem_t* subject, int initState)
{
	int i = 0;

	if(pipe(subject->semInfo) < 0)
	{
		printf("Uh oh. \n");
		exit(0);
	}

	for(i = 0; i < initState; ++i)
	{
		pipe_sem_signal(subject);
	}
}

void pipe_sem_wait(pipe_sem_t* subject)
{
	char u;

	read(subject->semInfo[0], &u, 1);
}

void pipe_sem_signal(pipe_sem_t* subject)
{
	int pid;
	pid = fork();

	if(pid < 0)
	{
		perror("Failed to implement unlock. \n");
		exit(1);
	}
	if(pid == 0)
	{
		write(subject->semInfo[1], "b", 1);
		exit(0); 
	}
}

