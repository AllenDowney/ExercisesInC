badlock: lock.c main.c
	gcc -Wall main.c lock.c -o badlock

goodlock: lock_bts.s main.c
	gcc -Wall main.c lock_bts.s -o goodlock

pthreadlock: mutex.c main.c
	gcc -Wall main.c mutex.c -o pthreadlock

example: example.c
	gcc -Wall example.c -o example -lpthread

array1: array.c lock.s
	gcc -g array.c lock.s -o array1 -lpthread

array2: array.c lock_bts.s
	gcc -g array.c lock_bts.s -o array2 -lpthread

array3: array.c pmutex.c
	gcc -g array.c pmutex.c -o array3 -lpthread

array4: array.c semlock.c semaphore.c cond.c
	gcc -g array.c semlock.c semaphore.c cond.c -o array4 -lpthread

clean:
	rm -f *~ badlock goodlock example
