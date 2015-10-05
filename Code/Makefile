CFLAGS=
CC = gcc
#---------------------------------------------------

ep2: ep2.c utils.o
	$(CC) $(CFLAGS) ep2.c utils.o -o ep2 -lreadline

utils.o: utils.h utils.c
	$(CC) $(CFLAGS) -c utils.c
