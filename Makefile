CC=gcc
CFLAGS=-Wall -ansi
OBJS=sasm.o

sasm: $(OBJS)
	$(CC) $(CFLAGS) -o sasm $(OBJS)

sasm.o:sasm.c mapping.h
