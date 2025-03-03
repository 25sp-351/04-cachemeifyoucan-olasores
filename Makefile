CC = gcc
CFLAGS = -Wall -Wextra

all: rod_cut_lru rod_cut_lfu

rod_cut_lru: main.o rod_cutting.o cache_lru.o
	$(CC) $(CFLAGS) -o rod_cut_lru main.o rod_cutting.o cache_lru.o

rod_cut_lfu: main.o rod_cutting.o cache_lfu.o
	$(CC) $(CFLAGS) -o rod_cut_lfu main.o rod_cutting.o cache_lfu.o

main.o: main.c rod_cutting.h
	$(CC) $(CFLAGS) -c main.c

rod_cutting.o: rod_cutting.c rod_cutting.h
	$(CC) $(CFLAGS) -c rod_cutting.c

cache_lru.o: cache_lru.c rod_cutting.h
	$(CC) $(CFLAGS) -c cache_lru.c

cache_lfu.o: cache_lfu.c rod_cutting.h
	$(CC) $(CFLAGS) -c cache_lfu.c

clean:
	rm -f *.o rod_cut_lru rod_cut_lfu