CC=gcc

all: mem z
mem: mem.c
	$(CC) -o $@ $^ -g
z: Zeroes.c
	$(CC) -o $@ $^ -g
clean:
	rm -f mem
	rm -f z
	rm -f vgcore.*
