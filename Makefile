cc = gcc
OS := $(shell uname)



ifeq ($(OS), Linux)
	path = /usr/bin/noc
endif
ifeq ($(OS), Darwin)
	path = /usr/local/bin/noc
endif



all: noc

noc: src/noc.c
	$(cc) -I inc -o $(path) src/noc.c src/globals.c src/logs.c src/syntax.c src/keywords.c -Wall -W -pedantic -lncurses

debug: src/noc.c
	$(cc) -I inc -DDEBUG -o $(path) src/noc.c src/globals.c src/logs.c -Wall -W -pedantic -lncurses

clean:
	rm -f $(path)
