CC=gcc
CFLAGS=-Wall -ansi -ggdb
OBJS=sasm.o symbol_table.o parsed_line.o

sasm: $(OBJS)
	$(CC) $(CFLAGS) -o sasm $(OBJS)

sasm.o:sasm.c mapping.h symbol_table.h parsed_line.h

symbol_table.o:symbol_table.c symbol_table.h

parsed_line.o:parsed_line.c parsed_line.h


# test bins

parse_test.o:parse_test.c parsed_line.h

parse_test: parse_test.o parsed_line.o
	$(CC) $(CFLAGS) -o parse_test parse_test.o parsed_line.o

# utils

clean:
	rm -f $(OBJS)
