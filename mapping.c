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
#include <stdlib.h>

#include "mapping.h"

int op_size(char *token)
{
	int i;
	for(i = 0; i < OPCODE_SET_SIZE; i++) {
		if(strcmp(opcode_table[i].token, token) == 0) {
			return opcode_table[i].size;
		}
	}
	return -1;
}

int op_code(char *token)
{
	int i;
	for(i = 0; i < OPCODE_SET_SIZE; i++) {
		if(strcmp(opcode_table[i].token, token) == 0) {
			return opcode_table[i].code;
		}
	}
	return -1;
}

char *op_token(int code)
{
	int i;
	for(i = 0; i < OPCODE_SET_SIZE; i++) {
		if(opcode_table[i].code == code) {
			return opcode_table[i].token;
		}
	}
	return NULL;
}


