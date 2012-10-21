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
#include "memory.h"
#include "mapping.h"

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

int main(void)
{
	char instr;
	/* read binary from stdin and load into mem */

	/* start processing at 0 */
	counter = 0;

	/* processing loop */
	while((instr = mem_read(counter)) != HALT_CODE) {
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
