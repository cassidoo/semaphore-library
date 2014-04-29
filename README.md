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

Here, the first argument �5� is the total number of reader/writer threads, and the following sequence �0 0 1 1 0� specifies the arriving order of readers 
(denoted by �0�) and writers (denoted by �1�). The last argument �1� specifies the time elapsed between two consecutive arrivals in the unit of second.

##What is the Reader-Writer problem?

Well, there's a lot of resources to look that up, but to sum up the "writer's priority" version that I have:

 * Reader and writer processes share an integer variable
 * Readers read the variable without changing its content
 * Writers may change the variable
 * Concurrent reads by several readers are allowed, but only one writer can write at a time
 * Readers and writers exclude each other
 * Arriving writers have priority over waiting readers; 
 a waiting or arriving reader can access the resource only when there is no writer waiting in the system (this is the "writer's priority" part)


