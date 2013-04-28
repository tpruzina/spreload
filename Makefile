CC=gcc
CFLAGS=-O2 -g

all: spreload.c
	$(CC) $(CFLAGS) spreload.c -o spreload

clean:
	rm -v ./spreload
