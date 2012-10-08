/*
 * ============================================================================
 *
 *       Filename:  mapper.c
 *
 *    Description:  Impl for opcode lookups/translations
 *
 *        Version:  1.0
 *        Created:  12-09-30 10:50:55 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd (), akydd@ualberta.net
 *   Organization:  
 *
 * ============================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "symbol_table.h"
#include "mapping.h"

int instr_size(char *token)
{
	int i;
	for(i = 0; i < OPCODE_SET_SIZE; i++) {
		if(strcmp(instr_table[i].token, token) == 0) {
			return instr_table[i].size;
		}
	}
	return -1;
}

int instr_code(char *token)
{
	int i;
	for(i = 0; i < OPCODE_SET_SIZE; i++) {
		if(strcmp(instr_table[i].token, token) == 0) {
			return instr_table[i].code;
		}
	}
	return -1;
}

char *instr_token(int code)
{
	int i;
	for(i = 0; i < OPCODE_SET_SIZE; i++) {
		if(instr_table[i].code == code) {
			return instr_table[i].token;
		}
	}
	return NULL;
}

int op_to_code(char *token)
{
	int i;
	for(i = 0; i < REG_SET_SIZE; i++) {
		if(strcmp(op_table[i].token, token) == 0) {
			return op_table[i].code;
		}
	}
	return -1;
}

int op_to_const(char *token)
{
	int code;
	int scan;

	/* First, try to convert to an int.
	 * Failing that, look for matching symbol. */
	if((scan = sscanf(token, "%d", &code)) != 1) {
		return find_value(token);
	} else {
		return code;
	}
}

char *op_token(int code)
{
	int i;
	for(i = 0; i < REG_SET_SIZE; i++) {
		if(op_table[i].code == code) {
			return op_table[i].token;
		}
	}
	return NULL;
}
