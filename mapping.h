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
#define INSTR_SET_SIZE 20

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

const int INSTR_CODE_TABLE[] = {
	LOAD_CODE,
	LOADI_CODE,
	STORE_CODE,
	STOREI_CODE,
	JMP_CODE,
	JMPZ_CODE,
	JMPN_CODE,
	JMPO_CODE,
	ADD_CODE,
	ADDR_CODE,
	SUB_CODE,
	SUBR_CODE,
	OUT_CODE,
	OUTC_CODE,
	OUTR_CODE,
	OUTRC_CODE,
	OUTI_CODE,
	OUTIC_CODE,
	HALT_CODE
};

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

const char *INSTR_STR_TABLE[] = {
	LOAD_STR,
	LOADI_STR,
	STORE_STR,
	STOREI_STR,
	JMP_STR,
	JMPZ_STR,
	JMPN_STR,
	JMPO_STR,
	ADD_STR,
	ADDR_STR,
	SUB_STR,
	SUBR_STR,
	OUT_STR,
	OUTC_STR,
	OUTR_STR,
	OUTRC_STR,
	OUTI_STR,
	OUTIC_STR,
	HALT_STR,
	DATA_STR
};

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

const int INSTR_SIZE_TABLE[] = {
	LOAD_SIZE,
	LOADI_SIZE,
	STORE_SIZE,
	STOREI_SIZE,
	JMP_SIZE,
	JMPZ_SIZE,
	JMPN_SIZE,
	JMPO_SIZE,
	ADD_SIZE,
	ADDR_SIZE,
	SUB_SIZE,
	SUBR_SIZE,
	OUT_SIZE,
	OUTC_SIZE,
	OUTR_SIZE,
	OUTRC_SIZE,
	OUTI_SIZE,
	OUTIC_SIZE,
	HALT_SIZE,
	DATA_SIZE
};

/* Registers for processor */
#define REG_SET_SIZE 4

#define A1_CODE 3
#define A2_CODE 2
#define R1_CODE 1
#define R2_CODE 0

const int REG_CODE_TABLE[] = {
	A1_CODE,
	A2_CODE,
	R1_CODE,
	R2_CODE
};

#define A1_STR "A!"
#define A2_STR "A2"
#define R1_STR "R1"
#define R2_STR "R2"

const char *REG_STR_TABLE[] = {
	A1_STR,
	A2_STR,
	R1_STR,
	R2_STR
};
