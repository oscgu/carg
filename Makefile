CC = cc
SRC = example.c
HEADER = carg.h
OBJ = $(SRC:.c=.o)
CFLAGS = -Os -pedantic -Wall -Wno-deprecated-declarations -Wextra -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=200809L

all: example

example: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:
clean:
	rm *.o
	rm example
