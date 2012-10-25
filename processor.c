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
void clear_flags();
void load();
void loadi();
void store();
void storei();
void jmp();
void jmpz();
void jmpn();
void jmpo();
void add();
void addr();
void sub();
void subr();
void out();
void outc();
void outr();
void outrc();
void outi();
void outic();


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
		(void)printf("Read instr %x\n", instr);
		(void)printf("A1: %d, A2: %d\n", A1, A2);
		(void)printf("R1: %d, R2: %d\n", R1, R2);
#endif
		process(instr);
	}

	exit(0);
}

void process(char code)
{
	static void (* const pf[]) (void) = { 
		&load, &loadi,
		&store, &storei,
		&jmp, &jmpz, &jmpn, &jmpo,
		&add, &addr,
		&sub, &subr,
		&out, &outc, &outr, &outrc, &outi, &outic
       	};

	int code_index = code - LOAD_CODE;
	if (code_index < sizeof(pf) / sizeof(*pf) &&
			code_index >= 0) {
		pf[code_index]();
	}
}

void clear_flags()
{
	flags = 0;
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
	*reg1 = memory[*reg2];
	*reg1 = (*reg1)<<8;
	*reg1 |= memory[(*reg2) + 1];
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

void jmp()
{
	counter += 2;
	int pos = (int)read_imm_value(counter);
	counter = pos;
}

void jmpz()
{
	if((flags & Z_FLAG) == Z_FLAG) {
		counter += 2;
		int pos = (int)read_imm_value(counter);
		counter = pos;
	} else {
		counter += 4;
	}
}

void jmpn()
{
	if((flags & N_FLAG) == N_FLAG) {
		counter += 2;
		int pos = (int)read_imm_value(counter);
		counter = pos;
	} else {
		counter += 4;
	}
}

void jmpo()
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
	clear_flags();

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
	clear_flags();

	char reg_code = memory[counter];
	short int *reg1 = get_reg1(reg_code);
	short int *reg2 = get_reg2(reg_code);

	int reg1_val = (int)(*reg1);
	int reg2_val = (int)(*reg2);

	/* check for overflow and other flags */
	int sum = reg1_val + reg2_val;

#ifdef DEBUG
	(void)printf("Added %d and %d to get %d\n", reg1_val, reg2_val, sum);
#endif
	if(sum > SHRT_MAX || sum < SHRT_MIN) {
		flags |= O_FLAG;
	} else {
		if (sum < 0) {
			flags |= N_FLAG;
		} else if (sum == 0) {
			flags |= Z_FLAG;
		}
		*reg1 = (short int)sum;
	}
	counter++;
}

void sub()
{
	counter++;
	clear_flags();

	char reg_code = memory[counter];
	short int *reg = get_reg1(reg_code);
	int reg_val = (int)(*reg);

	counter++;
	int imm_val = (int)read_imm_value(counter);

	/* 
	 * check for overflow.  If not, perform operation and set other
	 * flags
	 */
	reg_val -= imm_val;
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

void subr()
{
	counter++;
	clear_flags();

	char reg_code = memory[counter];
	short int *reg1 = get_reg1(reg_code);
	short int *reg2 = get_reg2(reg_code);

	int reg1_val = (int)(*reg1);
	int reg2_val = (int)(*reg2);

	/* check for overflow and other flags */
	reg1_val -= reg2_val;
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

void out()
{
	counter += 2;

	short int number = read_imm_value(counter);
	/* use %d to convert int to ASCII before output */
	(void)printf("%d", number);
	counter += 2;

}

void outc()
{
	counter += 2;

	short int character = read_imm_value(counter);
	/* use %c to treat value as ASCII char, no conversion */
	(void)printf("%c", character);
	counter += 2;
}

void outr()
{
	counter++;

	char code = memory[counter];
	short int *reg1 = get_reg1(code);
	(void)printf("%d", *reg1);
	counter++;
}

void outrc()
{
	counter++;

	char code = memory[counter];
	short int  *reg1 = get_reg1(code);
	(void)printf("%c", *reg1);
	counter++;
}

void outi()
{
	counter++;

	char code = memory[counter];
	short int *reg1 = get_reg1(code);
	int pos = (int)(*reg1);
	short int number = read_imm_value(pos);
	(void)printf("%d", number);
	counter++;
}

void outic()
{
	counter++;

	char code = memory[counter];
	short int *reg1 = get_reg1(code);
	int pos = (int)(*reg1);
	short int character = read_imm_value(pos);
	(void)printf("%c", character);
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
#ifdef DEBUG
	(void)printf("Read %d from %d\n", src, pos);
#endif
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
#ifdef DEBUG
	(void)printf("Stored value %d at %d\n", value, pos);
#endif
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
