FLAGS = -g -Wall -std=c99

queue_test: queue_test.c queue.c utils.c queue.h utils.h
	gcc $(FLAGS) queue_test.c queue.c utils.c -o queue_test -lpthread

queue: main.c queue.c utils.c queue.h utils.h
	gcc $(FLAGS) main.c queue.c utils.c -o queue -lpthread

queue_mutex: main.c queue_mutex.c utils.c queue.h utils.h
	gcc $(FLAGS) main.c queue_mutex.c utils.c -o queue_mutex -lpthread

queue_cond: main.c queue_cond.c utils.c queue.h utils.h
	gcc $(FLAGS) main.c queue_cond.c utils.c -o queue_cond -lpthread


