CC=gcc
AR=ar
SRC=src/main
DEPS=src/headers

proc: $(SRC)/Processor.c $(SRC)/fstrings.c
	$(CC) -o $@ $^ -I $(DEPS)
slib: $(SRC)/fstrings.c
	$(CC) -Wall -Werror -c -o fstrings.o $^ -I $(DEPS)
	$(AR) -rcs libsprocr.a fstrings.o
dlib: $(SRC)/fstrings.c
	$(CC) -Wall -Werror -c -fpic -o fstrings.o $^ -I $(DEPS)
	$(CC) -shared -o libsprocr.so fstrings.o
clean:
	rm -f proc
	rm -f vgcore.*
	rm -f *.o
	rm -f *.s
	rm -f *.a
	rm -f *.so
