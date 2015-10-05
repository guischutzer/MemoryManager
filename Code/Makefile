CFLAGS= -lreadline
CC = gcc
RM = rm
#---------------------------------------------------

all: ep2sh ep2 testebin clean

testebin: testebin.c
	$(CC) $(CFLAGS) testebin.c -o testebin

ep2sh: ep2sh.c utils.o
	$(CC) $(CFLAGS) ep2sh.c utils.o -o ep2sh

ep2: ep2.c utils.o
	$(CC) $(CFLAGS) ep2.c utils.o -o ep2

utils.o: utils.h utils.c
	$(CC) $(CFLAGS) -c utils.c

clean:
	mv ep2sh ../Test/
	mv ep2 ../Test/
	mv testebin ../Test/
	rm *.o
