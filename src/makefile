IDIR = .
CC = gcc
CFLAGS = -I$(IDIR) -g -Wall
_DEPS = hw4.h
DEPS = $(pathsubst %, $(IDIR)/%, $(_DEPS))

OBJ = hw4.o crypt.o histo.o invkey.o keygen.o solve.c

hw4: $(OBJ)
	$(CC) $^ -o $@

./%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f ./*.o hw4
