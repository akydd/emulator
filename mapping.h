/*
 * ============================================================================
 *
 *       Filename:  mapping.h
 *
 *    Description:  Lookup tables for instruction set and register string
 *    		    representations, bytecode, and instruction sizes.
 *
 *        Version:  1.0
 *        Created:  12-09-18 09:09:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd (), akydd@ualberta.net
 *   Organization:  
 *
 * ============================================================================
 */

/* opcodes for processor */
#define OPCODE_SET_SIZE 20

/* range is {49} U [96, 113] */
#define LOAD_CODE 0x60
#define LOADI_CODE 0x61
#define STORE_CODE 0x62
#define STOREI_CODE 0x63
#define JMP_CODE 0x64
#define JMPZ_CODE 0x65
#define JMPN_CODE 0x66
#define JMPO_CODE 0x67
#define ADD_CODE 0x68
#define ADDR_CODE 0x69
#define SUB_CODE 0x6a
#define SUBR_CODE 0x6b
#define OUT_CODE 0x6c
#define OUTC_CODE 0x6d
#define OUTR_CODE 0x6e
#define OUTRC_CODE 0x6f
#define OUTI_CODE 0x70
#define OUTIC_CODE 0x71
#define HALT_CODE 0x31

#define LOAD_STR "LOAD"
#define LOADI_STR "LOADI"
#define STORE_STR "STORE"
#define STOREI_STR "STOREI"
#define JMP_STR "JMP"
#define JMPZ_STR "JMPZ"
#define JMPN_STR "JMPN"
#define JMPO_STR "JMPO"
#define ADD_STR "ADD"
#define ADDR_STR "ADDR"
#define SUB_STR "SUB"
#define SUBR_STR "SUBR"
#define OUT_STR "OUT"
#define OUTC_STR "OUTC"
#define OUTR_STR "OUTR"
#define OUTRC_STR "OUTRC"
#define OUTI_STR "OUTI"
#define OUTIC_STR "OUTIC"
#define HALT_STR "HALT"
#define DATA_STR "DATA"

/* instruction bytesizes */
#define LOAD_SIZE 4
#define LOADI_SIZE 2
#define STORE_SIZE 4
#define STOREI_SIZE 2
#define JMP_SIZE 4
#define JMPZ_SIZE 4
#define JMPN_SIZE 4
#define JMPO_SIZE 4
#define ADD_SIZE 4
#define ADDR_SIZE 2
#define SUB_SIZE 4
#define SUBR_SIZE 2
#define OUT_SIZE 4
#define OUTC_SIZE 4
#define OUTR_SIZE 2
#define OUTRC_SIZE 2
#define OUTI_SIZE 2
#define OUTIC_SIZE 2
#define HALT_SIZE 2
#define DATA_SIZE 2

/* structure encapsulated info about each instruction */
struct instr_entry {
	int code;	/* opcode */
	char *token;	/* string representation */
	int size;	/* total byte size */
	int op1_is_const;	/* 1 if op1 takes a constant value */
	int op2_is_const;	/* 1 if op2 takes a constant value */
};

static const struct instr_entry instr_table[] = {
	{LOAD_CODE, LOAD_STR, LOAD_SIZE, 0, 1},
	{LOADI_CODE, LOADI_STR, LOADI_SIZE, 0, 0},
	{STORE_CODE, STORE_STR, STORE_SIZE, 0, 1},
	{STOREI_CODE, STOREI_STR, STOREI_SIZE, 0, 0},
	{JMP_CODE, JMP_STR, JMP_SIZE, 1, 0},
	{JMPZ_CODE, JMPZ_STR, JMPZ_SIZE, 1, 0},
	{JMPN_CODE, JMPN_STR, JMPN_SIZE, 1, 0},
	{JMPO_CODE, JMPO_STR, JMPO_SIZE, 1, 0},
	{ADD_CODE, ADD_STR, ADD_SIZE, 0, 1},
	{ADDR_CODE, ADDR_STR, ADDR_SIZE, 0, 0},
	{SUB_CODE, SUB_STR, SUB_SIZE, 0, 1},
	{SUBR_CODE, SUBR_STR, SUBR_SIZE, 0, 0},
	{OUT_CODE, OUT_STR, OUT_SIZE, 1, 0},
	{OUTC_CODE, OUTC_STR, OUTC_SIZE, 1, 0},
	{OUTR_CODE, OUTR_STR, OUTR_SIZE, 0, 0},
	{OUTRC_CODE, OUTRC_STR, OUTRC_SIZE, 0, 0},
	{OUTI_CODE, OUTI_STR, OUTI_SIZE, 0, 0},
	{OUTIC_CODE, OUTIC_STR, OUTIC_SIZE, 0, 0},
	{HALT_CODE, HALT_STR, HALT_SIZE, 0, 0},
	{-1, DATA_STR, DATA_SIZE, 1, 0}
};

int instr_size(char *);
int instr_code(char *);
char *instr_token(int);
int op1_labelled(char *);
int op2_labelled(char *);

/* Registers for processor */
#define REG_SET_SIZE 4

#define A1_CODE 3
#define A2_CODE 2
#define R1_CODE 1
#define R2_CODE 0

#define A1_STR "A1"
#define A2_STR "A2"
#define R1_STR "R1"
#define R2_STR "R2"

struct op_entry {
	int code;
	char *token;
};

static const struct op_entry op_table[] = {
	{A1_CODE, A1_STR},
	{A2_CODE, A2_STR},
	{R1_CODE, R1_STR},
	{R2_CODE, R2_STR}
};

int op_to_code(char *);
int op_to_const(char *);
char *op_token(int);
