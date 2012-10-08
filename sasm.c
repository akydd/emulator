/*
 * ============================================================================
 *
 *       Filename:  sasm.c
 *
 *    Description:  Assembler. Converts assembly language into machine code.
 *    
 *    Ex 1:
 *    
 *    _______ LOADI R2,A2 # load contents of address in A2 into R2
 *    
 *    gets translated to the following two bytes, in binary.
 *    
 *    [01100001][10000000]
 *
 *
 *    Ex 2:
 *
 *    _______ LOAD R1,4 # load value 4 into R1
 *
 *    gets translated to the following 4 bytes, in binary.
 *
 *    [01100000][11000000][00000000][00000100]
 *
 *
 *    Ex 3:
 *
 *    _______ OUT -2 # output the integer -2
 *
 *    gets translated to the following 4 bytes, in binary.
 *
 *    [01101100][00000000][11111111][11111110]
 *
 *
 *
 * Processing is done in 3 steps:
 * 1. Read all stdin and store in buffer
 * 2. Process each line form buffer, building memory map for labels
 * 2. Process each line from buffer, translating instructions into opcodes
 *    and subing in memory address value for labels.  Output
 *    result to stdout.
 * 
 *
 *        Version:  1.0
 *        Created:  12-09-18 09:22:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd (), akydd@ualberta.net
 *   Organization:  
 *
 * ============================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mapping.h"		/* map language tokens to opcodes */
#include "symbol_table.h"	/* symbol memory map */
#include "parsed_line.h"	/* adt for parsing input file */

#define BLOCK 60

void store_char(int);

char *buffer;
int max = BLOCK;
int char_count = 0;

/* symbol table */
struct entry *symbol_table = NULL;

/* data struct to hold parsed file */
struct parsed_line *parsed_lines = NULL;

int main(void)
{
	/* init buffer */
	int max = BLOCK;
	buffer = malloc(sizeof(char) * max);

	/* read stdin */
	int char_in;
	while((char_in = getchar()) != EOF) {
		store_char(char_in);
	}
	/* null terminate string */
	buffer[char_count] = '\0';

	/* copy buffer contents for tokenizing */
	char *buf_cpy = malloc(sizeof(char) * (strlen(buffer) + 1));
	(void)strcpy(buf_cpy, buffer);

	/* track the memory address while parsing instructions */
	int address = 0;
	struct parsed_line *instr = NULL;

	/* tokenize buffer by newlines */
	char *line = NULL;
	line = strtok(buf_cpy, "\n");
	while(line != NULL) {
		/* (void)printf("Line is: %s\n", line); */
		instr = parse_line(line);
		add_parsed_line(instr);

		/* store label in symbol table, if needed */
		if(instr->label != NULL) {
			add_symbol(instr->label, address);
		}

		/* set address start for next instr */
		address += instr_size(instr->instruction);

		/* get next token */
		line = strtok(NULL, "\n");
	}

	/* second pass - translate to binary */
	instr = parsed_lines;
	while(instr->next != NULL) {
		int code = 0;

		/* data */
		if(strcmp(instr->instruction, DATA_STR) == 0) {
			(void)putchar(op_to_const(instr->op1));
		} else {
			/*instruction */
			(void)putchar(instr_code(instr->instruction));

			/* op1 */
			if(instr->op1 != NULL) {
				code = op_to_code(instr->op1);
				if (code < 0) {
					code = op_to_const(instr->op1);
				}
				(void)putchar(code);
			}

			/* op2 */
			if(instr->op2 != NULL) {
				code = op_to_code(instr->op2);
				if(code < 0) {
					code = op_to_const(instr->op2);
				}
				(void)putchar(code);
			}
		}
		instr = instr->next;
	}

	free(buffer);
	free(buf_cpy);
	delete_parsed_lines();
	delete_symbol_table();
	exit(EXIT_SUCCESS);
}

void store_char(int char_in)
{
	char_count++;
	if(char_count > max) {
		max += BLOCK;
		buffer = realloc(buffer, max);
	}
	buffer[char_count - 1] = (char)char_in;
}
