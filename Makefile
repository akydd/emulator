CC=gcc
CFLAGS=-Wall -ansi
OBJS=sasm.o symbol_table.o parsed_line.o

sasm: $(OBJS)
	$(CC) $(CFLAGS) -o sasm $(OBJS)

sasm.o:sasm.c mapping.h symbol_table.h parsed_line.h

symbol_table.o:symbol_table.c symbol_table.h

parsed_line.o:parsed_line.c parsed_line.h

clean:
	rm -f $(OBJS)
