CC=gcc
SRC=src/main
DEPS=src/headers

proc: $(SRC)/Processor.c $(SRC)/fstrings.c
	$(CC) -o $@ $^ -I $(DEPS)
clean:
	rm -f proc
	rm -f vgcore.*
