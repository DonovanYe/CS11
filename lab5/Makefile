#
# CS 11 C track: Makefile for assignment 5.
#

CC = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic -Wuninitialized

lab5_array: lab5_array.o memcheck.o
	$(CC) lab5_array.o memcheck.o -o lab5_array

memcheck.o: memcheck.c memcheck.h
	$(CC) $(CFLAGS) -c memcheck.c

lab5_array.o: lab5_array.c memcheck.h
	$(CC) $(CFLAGS) -c lab5_array.c

check:
	c_style_check triangle_game.c

clean:
	rm -f *.o lab5_array memcheck
