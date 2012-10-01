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
#include "mapping.h"
#include "symbol_table.h"

#define BLOCK 60

void store_char(int);

char *buffer;
int max = BLOCK;
int char_count = 0;

/* symbol table */
struct entry *symbol_table = NULL;

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

	char *token = malloc(sizeof(char) * (strlen(buffer) + 1));
	char *result = NULL;
	(void)strcpy(token, buffer);
	result = strtok(token, "\n");
	while(result != NULL) {
		(void)printf("result is: %s\n", result);
		result = strtok(NULL, "\n");
	}


	/* first pass - map memory values to symbols */

	free(buffer);
	free(token);
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
