CC=gcc

all: mem z
mem: Mem.c
	$(CC) -o $@ $^ 
z: Zeroes.c
	$(CC) -o $@ $^
