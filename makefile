rw_tests: rw_tests.o pipe_sem.o
	gcc -o rw_tests rw_tests.o pipe_sem.o -lpthread

rw_tests.o: rw_tests.c
	gcc -c rw_tests.c

pipe_sem.o: pipe_sem.c pipe_sem.h
	gcc -c pipe_sem.c

clean:
	rm *.o
