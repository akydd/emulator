/*
 * ============================================================================
 *
 *       Filename:  processor.c
 *
 *    Description:  Processor for the emulator
 *
 *        Version:  1.0
 *        Created:  12-10-20 08:07:52 PM
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
#include "mapping.h"

/* memory module */
#define MEM_LAST_INDEX 32767
char memory[MEM_LAST_INDEX];

/* program counter */
int counter;

/* 2-byte data registers */
short int R1;
short int R2;

/* 2-byte address registers */
short int A1;
short int A2;

/* flags */
#define Z_FLAG 1<<0
#define N_FLAG 1<<1
#define O_FLAG 1<<2
short int flags = 0;

void process(char);
void set_flags();

int main(void)
{
	/* read binary from stdin and load into mem */
	int input;
	char *mem_ptr = memory;
	while((input = getchar()) != EOF) {
		*mem_ptr = (char)input;
#ifdef DEBUG
		(void)printf("%c", (char)input);
#endif
		mem_ptr++;
	}

	/* main processing loop */
	counter = 0;
	char instr;
	while((instr = memory[counter]) != HALT_CODE) {
#ifdef DEBUG
		(void)printf("Read code %c\n", instr);
#endif
		counter++;
		process(instr);
		set_flags();
	}

	exit(0);
}

void process(char code)
{
	switch(code) {
		case LOAD_CODE:
			break;
		default:
			break;
	}
}

void set_flags()
{

}
