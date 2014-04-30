Semaphore Library
========================

##What

In this project (for an operating systems class), a C library was to be developed to implement a semaphore based on unnamed pipe.
Test code was to be developed to solve a special version of readers-writer problem by using this library.

##How

To mess around this project, first, of course, you have to run `make`, and then your commands for launching the program follow this:

	rw_test <number of arriving threads> <a sequence of 0 and 1 separated by a blankspace> <thread arrival interval>

So, for example, to simulate the scenario that 5 threads arriving (i.e., being created) according to the following timings (where each time is in seconds): 
reader1 at time 0, reader2 at time 1, writer1 at time 2, writer2 at time 3, and reader3 at time 4, the command will be:

	rw_test 5 0 0 1 1 0 1

Here, the first argument “5” is the total number of reader/writer threads, and the following sequence “0 0 1 1 0” specifies the arriving order of readers 
(denoted by “0”) and writers (denoted by “1”). The last argument “1” specifies the time elapsed between two consecutive arrivals in the unit of second.

##Things you might care about

###What is a semaphore?
Great question, my darling.
According to Wikipedia, a semaphore is a variable or abstract data type that is used for controlling access, by multiple processes, 
to a common resource in a parallel programming or a multi user environment.

So basically, if you want to have multiple threads going, but you want to protect some parts of your code from being run by multiple things at once, you'd use a semaphore.

There's usually some semaphore variable (often called `mutex`, but there's other kinds) that tracks when a chunk of code is being used by a process.  

The typical functions in a semaphore include:
 * `wait`: Decrements the value of semaphore variable by 1.  If the value becomes negative, the process that is executing wait is added to the semaphore's queue.
 * `signal`: Increments the value of semaphore variable by 1.  If the pre-increment value was negative (meaning there are processes waiting for a resource), it transfers a waiting process from the semaphore's waiting queue to the ready queue after the increment.

I hope that makes sense.  You'll notice I implemented these two functions, as well as an `init` function.
 
###What is the Reader-Writer problem?

Well, there's a lot of resources to look that up, but to sum up the "writer's priority" version that I have:

 * Reader and writer processes share an integer variable
 * Readers read the variable without changing its content
 * Writers may change the variable
 * Concurrent reads by several readers are allowed, but only one writer can write at a time
 * Readers and writers exclude each other
 * Arriving writers have priority over waiting readers; 
 a waiting or arriving reader can access the resource only when there is no writer waiting in the system (this is the "writer's priority" part)
 
Get it?  Got it.  So, now you can see that it's necessary to solve the Reader-Writer problem with semaphores, because they (meaning the reader and the writer) mess with shared content.


