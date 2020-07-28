CC = gcc
CFLAGS = -Wall -g

program: program.o guiao0.o
guiao0.o: guiao0.h guiao0.c
program.o: guiao0.h program.c

clean:
	rn -f program *.o
