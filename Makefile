cc = gcc
OS := $(shell uname)



ifeq ($(OS), Linux)
	target = /usr/bin/noc
endif
ifeq ($(OS), Darwin)
	target = /usr/local/bin/noc
endif



all: noc

noc: noc.c
	$(cc) -o $(target) noc.c -Wall -W -pedantic -lncurses

clean:
	rm -f $(target)
