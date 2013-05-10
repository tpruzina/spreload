CC=gcc
CFLAGS=-O2 -g

all: spreload spreload.so

spreload: spreload.c
	$(CC) $(CFLAGS) spreload.c -o spreload

spreload.so: spreload_profile.c
	$(CC) $(CFLAGS) -shared -fPIC spreload_profile.c -o sprofile.so -ldl

clean:
	rm -v ./spreload
