/*
 * ============================================================================
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
 * ============================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "parsed_line.h"

void add_parsed_line(struct parsed_line *instr)
{
	/* add node to END of list */
	if(parsed_lines == NULL) {
		parsed_lines = instr;
	} else {
		struct parsed_line *search_ptr = parsed_lines;
		while(search_ptr->next != NULL) {
			search_ptr = search_ptr->next;
		}
		search_ptr->next = instr;
	}
}

struct parsed_line *parse_line(char *line) {
	int offset;

	/*  get mem for struct */
	struct parsed_line *new_line = malloc(sizeof(struct parsed_line));

	/* parse line to get each field */
	char *search_ptr = line;
	char *end_ptr = search_ptr + 1;

	/* label */
	new_line->label = NULL;
	if (isspace(*search_ptr) == 0) {
		while(isspace(*end_ptr) == 0) {
			end_ptr++;
		}
		/* set label */
		offset = end_ptr - search_ptr;
		new_line->label = malloc(sizeof(char) * offset);
		(void)strncpy(new_line->label, search_ptr, offset);
	}

	/* instruction */
	search_ptr = line + 8;
	end_ptr = search_ptr + 1;
	new_line->instruction = NULL;
	while(isspace(*end_ptr) == 0) {
		end_ptr++;
	}
	/* set instr */
	offset = end_ptr - search_ptr;
	new_line->instruction = malloc(sizeof(char) * offset);
	(void)strncpy(new_line->instruction, search_ptr, offset);

	/* set size */
	new_line->size = malloc(sizeof(int));
	/* TODO call fn to get size */
	new_line->size = 4;

	/* skip single blank spaces (we need to halt on newline) */
	search_ptr = end_ptr;
	while(*search_ptr == ' ') {
		search_ptr++;
	}

	/* op1 */
	new_line->op1 = NULL;
	/* another alnum char means op1 is present */
	if(isalnum(*search_ptr) != 0) {
		end_ptr = search_ptr + 1;
		while(isalnum(*end_ptr) != 0) {
			end_ptr++;
		}
		offset = end_ptr - search_ptr;
		/* save op1 */
		new_line->op1 = malloc(sizeof(char) * offset);
		(void)strncpy(new_line->op1, search_ptr, offset);
	}

	/* skip single blank spaces (we need to halt on newline) */
	search_ptr = end_ptr;
	while(*search_ptr == ' ') {
		search_ptr++;
	}

	/* op2 */
	new_line->op2 = NULL;
	/* if we haven't hit newline or comment delim, expect op2 */
	if(*search_ptr != '#' && *search_ptr != '\n') {
		/* op2 */
		while(isalnum(*search_ptr) == 0) {
			search_ptr++;
		}
		end_ptr = search_ptr + 1;
		while(isalnum(*end_ptr) != 0) {
			end_ptr++;
		}
		offset = end_ptr - search_ptr;
		/* save op2 */
		new_line->op2 = malloc(sizeof(char) * offset);
		(void)strncpy(new_line->op2, search_ptr, offset);
	}

	return new_line; 
}

void delete_parsed_lines()
{
	struct parsed_line *search_ptr = parsed_lines;
	struct parsed_line *next_ptr;
	while(search_ptr != NULL) {
		next_ptr = search_ptr->next;
		if(search_ptr->label != NULL) {
			free(search_ptr->label);
		}
		free(search_ptr->instruction);
		if (search_ptr->op1 != NULL) {
			free(search_ptr->op1);
		}
		if(search_ptr->op2 != NULL) {
			free(search_ptr->op2);
		}
		free(search_ptr->size);
		search_ptr = next_ptr;
	}
}
