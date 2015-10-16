CFLAGS = -Wall -O2 -ansi -pedantic -Wno-unused-result -lreadline
CC = gcc
RM = rm
#---------------------------------------------------

all: ep2 clean

ep2: main.o fit.o page.o utils.o io.o
	$(CC) -o ep2 main.o fit.o page.o utils.o io.o $(CFLAGS)

main.o: main.c utils.h fit.h page.h io.h
	$(CC) -c main.c $(CFLAGS)

fit.o: fit.h fit.c utils.h io.h
	$(CC) -c fit.c $(CFLAGS)

page.o: page.h page.c utils.h io.h
	$(CC) -c page.c $(CFLAGS)

io.o: io.h io.c utils.h
	$(CC) -c io.c $(CFLAGS)

utils.o: utils.h utils.c
	$(CC) -c utils.c $(CFLAGS)

clean:
	mkdir -p ../bin
	mv ep2 ../bin/
	rm *.o
