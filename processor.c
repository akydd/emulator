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
#include <limits.h>
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
short int *get_reg1(char);
short int *get_reg2(char);
short int read_imm_value(int);
void write_imm_value(short int, int);
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

void load()
{
	counter++;

	char reg_code = memory[counter];
	short int *reg1 = get_reg1(reg_code);
	counter++;
	short int src = read_imm_value(counter);
	*reg1 = src;
	counter += 2;
}

void loadi()
{
	counter ++;

	char reg_code = memory[counter];
	short int *reg1 = get_reg1(reg_code);
	short int *reg2 = get_reg2(reg_code);
	*reg1 = *reg2;
	counter++;
}

void store()
{
	counter++;

	char reg_code = memory[counter];
	short int *reg = get_reg1(reg_code);
	counter++;
	int pos = (int)read_imm_value(counter);
	write_imm_value(*reg, pos);
	counter += 2;
}

void storei()
{
	counter++;

	char reg_code = memory[counter];
	short int *reg1 = get_reg1(reg_code);
	short int *reg2 = get_reg2(reg_code);
	int pos = (int)(*reg2);
	write_imm_value(*reg1, pos);
	counter++;
}

void jump()
{
	counter += 2;
	int pos = (int)read_imm_value(counter);
	counter = pos;
}

void jump_z()
{
	if((flags & Z_FLAG) == Z_FLAG) {
		counter += 2;
		int pos = (int)read_imm_value(counter);
		counter = pos;
	} else {
		counter += 4;
	}
}

void jump_n()
{
	if((flags & N_FLAG) == N_FLAG) {
		counter += 2;
		int pos = (int)read_imm_value(counter);
		counter = pos;
	} else {
		counter += 4;
	}
}

void jump_o()
{
	if((flags & O_FLAG) == O_FLAG) {
		counter += 2;
		int pos = (int)read_imm_value(counter);
		counter = pos;
	} else {
		counter += 4;
	}
}

void add()
{
	counter++;

	char reg_code = memory[counter];
	short int *reg = get_reg1(reg_code);
	int reg_val = (int)(*reg);

	counter++;
	int imm_val = (int)read_imm_value(counter);

	/* 
	 * check for overflow.  If not, perform operation and set other
	 * flags
	 */
	reg_val += imm_val;
	if(reg_val > SHRT_MAX || reg_val < SHRT_MIN) {
		flags |= O_FLAG;
	} else {
		if(reg_val < 0) {
			flags |= N_FLAG;
		} else if (reg_val == 0) {
			flags |= Z_FLAG;
		}
		*reg = (short int)reg_val;
	}
	counter += 2;
}

void addr()
{
	counter++;

	char reg_code = memory[counter];
	short int *reg1 = get_reg1(reg_code);
	short int *reg2 = get_reg2(reg_code);

	int reg1_val = (int)(*reg1);
	int reg2_val = (int)(*reg2);

	/* check for overflow and other flags */
	reg1_val += reg2_val;
	if(reg1_val > SHRT_MAX || reg1_val < SHRT_MAX) {
		flags |= O_FLAG;
	} else {
		if (reg1_val < 0) {
			flags |= N_FLAG;
		} else if (reg1_val == 0) {
			flags |= Z_FLAG;
		}
		*reg1 = (short int)reg1_val;
	}
	counter++;
}

/*
 * Starting at pos, reads two bytes and returns combined values as a short int.
 * Does not move the program counter.
 */
short int read_imm_value(int pos)
{
	short int src = memory[pos];
	src = src<<8;
	src |= memory[pos + 1];
	return src;
}

/* 
 * Stores the given 16-bit value in two consecutive entries in the memory
 * array, starting at pos.
 * Does not move the counter.
 */
void write_imm_value(short int value, int pos)
{
	char byte1 = (char)(value>>8);
	char byte2 = (char)value;
	memory[pos] = byte1;
	memory[pos + 1] = byte2;
}

/*
 * Decodes the char code to figure out which register is requested for the
 * first register argument of the instruction.  Returns a pointer to the
 * requested register.
 */
short int *get_reg1(char code)
{
	short int *reg_ptr = NULL;

	/* test rightmost 2 bits */
	switch(code & 0x03) {
		case R2_CODE:
			reg_ptr = &R2;
			break;
		case R1_CODE:
			reg_ptr = &R1;
			break;
		case A2_CODE:
			reg_ptr = &A2;
			break;
		case A1_CODE:
			reg_ptr = &A1;
			break;
		default:
			reg_ptr = NULL;
	}

	return reg_ptr;
}


/*
 * Decodes the char code to figure out which register is requested for the
 * second register argument of the instruction.  Returns a pointer to the
 * requested register.
 */
short int *get_reg2(char code)
{
	short int *reg_ptr = NULL;

	/* test leftmost 2 bits */
	char tester = (code & 0xc0)>>6;
	switch(tester) {
		case R2_CODE:
			reg_ptr = &R2;
			break;
		case R1_CODE:
			reg_ptr = &R1;
			break;
		case A2_CODE:
			reg_ptr = &A2;
			break;
		case A1_CODE:
			reg_ptr = &A1;
			break;
		default:
			reg_ptr = NULL;
	}

	return reg_ptr;
}
