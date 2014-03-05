IDIR = .
CC = gcc
CFLAGS = -I$(IDIR) -g -Wall


OBJ = keyg.o

keyg: $(OBJ)
	$(CC) $^ -o $@

./%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< 

.PHONY: clean

clean:
	rm -f ./*.o keyg
