CC=gcc
CFLAGS=-g3 -ggdb3

all: main.c
	$(CC) $(CFLAGS) main.c -o preload
