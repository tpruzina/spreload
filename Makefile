CC=gcc
CFLAGS=-O2 -g
PREFIX=/usr/local
LD_PREFIX=/usr/lib
all: spreload spreload.so

spreload: spreload.c
	$(CC) $(CFLAGS) spreload.c -o spreload

spreload.so: spreload_profile.c
	$(CC) $(CFLAGS) -shared -fPIC spreload_profile.c -o sprofile.so -ldl


install: all
	cp ./spreload ${PREFIX}/bin
	cp ./sprofile.so ${LD_PREFIX}/

uninstall:
	rm ${PREFIX}/bin/spreload
	rm  ${LD_PREFIX}/sprofile.so

clean:
	rm ./spreload
