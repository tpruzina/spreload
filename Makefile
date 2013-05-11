CC=gcc
CFLAGS=-O2 -g
PREFIX=/usr/local

all: spreload spreload.so

spreload: spreload.c
	$(CC) $(CFLAGS) spreload.c -o spreload

spreload.so: spreload_profile.c
	$(CC) $(CFLAGS) -shared -fPIC spreload_profile.c -o sprofile.so -ldl

install: all
	cp ./spreload		${PREFIX}/bin
	cp ./spreload-profile	${PREFIX}/bin
	cp ./sprofile.so	${PREFIX}/lib

uninstall:
	rm -f ${PREFIX}/bin/spreload
	rm -f ${PREFIX}/bin/spreload-profile
	rm -f ${PREFIX}/lib/sprofile.so

clean:
	rm ./spreload
