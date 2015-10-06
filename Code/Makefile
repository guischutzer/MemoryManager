CFLAGS= -g -Wall -O2 -ansi -pedantic -Wno-unused-result
CC = gcc
RM = rm
#---------------------------------------------------

all: ep2 testebin clean

ep2: main.o utils.o io.o
	$(CC) -lreadline -o ep2 main.o utils.o io.o

testebin: testebin.c
	$(CC) $(CFLAGS) testebin.c -o testebin

main.o: main.c utils.h io.h
	$(CC) $(CFLAGS) -lreadline -c main.c

io.o: io.h io.c utils.h
	$(CC) $(CFLAGS) -c io.c

utils.o: utils.h utils.c
	$(CC) $(CFLAGS) -c utils.c




clean:
	mkdir -p ../bin
	mv ep2 ../bin/
	mv testebin ../bin/
	rm *.o
