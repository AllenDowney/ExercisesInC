CC = gcc
CFLAGS = -g -Wall
GLIB_FLAGS = -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
LIBS = -lglib-2.0

list_errors: list_errors.c
	$(CC) -o $@ $^ $(CFLAGS)

word_count: word_count.c
	$(CC) -o $@ $^ $(CFLAGS) $(GLIB_FLAGS) $(LIBS)
