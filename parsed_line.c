/*
 * =============================================================================
 *
 *       Filename:  parsed_line.c
 *
 *    Description:  Impl for parsed_line
 *
 *        Version:  1.0
 *        Created:  12-09-23 08:47:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd (), akydd@ualberta.net
 *   Organization:  
 *
 * =============================================================================
 */
#include <stdlib.h>
#include <string.h>
#include "parsed_line.h"
#include "mapping.h"

void add(char *inst, char *op1, char *op2)
{
	struct parsed_line *new_line = create_new(instr, op1, op2);

	/* add node to END of list */
	if(parsed_line == NULL) {
		parsed_lines = new_line;
	} else {
		struct parsed_line *search_ptr = parsed_lines;
		while(search_ptr->next != NULL) {
			search_ptr = search_ptr->next;
		}
		search_ptr->next = new_line;
	}
}

struct parsed_line *create_new(char *instr, char *op1, char *op2)
{
	/*  get mem for struct */
	struct parsed_line *new_line = malloc(sizeof(struct parsed_line));

	/* get mem for fields and set values */
	/* instruction */
	new_line->instruction = malloc(sizeof(char) * (strlen(instr)+1));
	(void)strcpy(new_line->instruction, instr);

	/* op codes could be null */
	if(op1 != NULL) {
		new_line->op1 = malloc(sizeof(char) * (strlen(op1) + 1));
		(void)strcpy(new_line->op1, op1);
	}
	if(op2 != NULL) {
		new_line->op2 = malloc(sizeof(char) * (strlen(op2) + 1));
		(void)strcpy(new_line->op2, op2);
	}

	new_line->size = malloc(sizeof(int));
	new_line->size = instruction_size(inst);

	return new_line;
}
