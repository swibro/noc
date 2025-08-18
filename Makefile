all: texty

texty: rewrite.c
	gcc -o /usr/bin/texty rewrite.c -Wall -W -pedantic -lncurses

clean:
	rm -f /usr/bin/texty
