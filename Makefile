cc = gcc
OS := $(shell uname)



ifeq ($(OS), Linux)
	path = /usr/bin/noc
endif
ifeq ($(OS), Darwin)
	path = /usr/local/bin/noc
endif



all: noc

noc: noc.c
	$(cc) -o $(path) noc.c -Wall -W -pedantic -lncurses

clean:
	rm -f $(path)
