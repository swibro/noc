all: noc

noc: noc.c
	gcc -o /usr/bin/noc noc.c -Wall -W -pedantic -lncurses

clean:
	rm -f /usr/bin/noc
