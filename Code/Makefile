CFLAGS=
CC = gcc
#---------------------------------------------------

all: ep2sh ep2

ep2sh: ep2sh.c utils.o
	$(CC) $(CFLAGS) ep2sh.c utils.o -o ep2sh -lreadline	

ep2: ep2.c utils.o
	$(CC) $(CFLAGS) ep2.c utils.o -o ep2 -lreadline

utils.o: utils.h utils.c
	$(CC) $(CFLAGS) -c utils.c


