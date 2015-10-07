CFLAGS = -Wall -O2 -ansi -pedantic -Wno-unused-result -lreadline
CC = gcc
RM = rm
#---------------------------------------------------

all: ep2 testebin clean

ep2: main.o utils.o io.o
	$(CC) -o ep2 main.o utils.o io.o $(CFLAGS)

testebin: testebin.c
	$(CC) testebin.c -o testebin $(CFLAGS)

main.o: main.c utils.h io.h
	$(CC) -c main.c $(CFLAGS)

io.o: io.h io.c utils.h
	$(CC) -c io.c $(CFLAGS)

utils.o: utils.h utils.c
	$(CC) -c utils.c $(CFLAGS) 

clean:
	mkdir -p ../bin
	mv ep2 ../bin/
	mv testebin ../bin/
	rm *.o
