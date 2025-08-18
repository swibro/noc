cc = gcc
OS := $(shell uname)

ifeq ($(OS), Linux)
	target = noc-linux
endif
ifeq ($(OS), Darwin)
	target = noc-darwin
endif

noc-linux: noc.c
	gcc -o /usr/bin/noc noc.c -Wall -W -pedantic -lncurses

noc-darwin: noc.c
	gcc -o /usr/local/bin/noc noc.c -lncurses

clean:
	rm -f /usr/bin/noc
