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
#include <stdio.h>
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
	char *search_ptr = line;
	char *end_ptr;

	/* get mem for struct */
	struct parsed_line *new_line = malloc(sizeof(struct parsed_line));
	new_line->next = NULL;

	/* label */
	new_line->label = NULL;
	end_ptr = strchr(line, ' ');
	if (end_ptr != search_ptr) {
		offset = end_ptr - search_ptr;
		/* set label */
		new_line->label = malloc(sizeof(char) * (offset + 1));
		(void)strncpy(new_line->label, search_ptr, offset);
		new_line->label[offset] = '\0';
	}

	/* instruction */
	search_ptr = line + 8;
	end_ptr = search_ptr + 1;
	new_line->instruction = NULL;
	while(isalpha(*end_ptr) != 0) {
		end_ptr++;
	}
	offset = end_ptr - search_ptr;
	/* set instr */
	new_line->instruction = malloc(sizeof(char) * (offset + 1));
	(void)strncpy(new_line->instruction, search_ptr, offset);
	new_line->instruction[offset] = '\0';

	/* skip single blank spaces (we need to halt on '\0') */
	search_ptr = end_ptr;
	while(*search_ptr == ' ') {
		search_ptr++;
	}

	/* op1 */
	new_line->op1 = NULL;
	/* another alpha/num char means op1 is present */
	if(isalnum(*search_ptr) != 0) {
		end_ptr = search_ptr + 1;
		while(isalnum(*end_ptr) != 0) {
			end_ptr++;
		}
		offset = end_ptr - search_ptr;
		/* set op1 */
		new_line->op1 = malloc(sizeof(char) * (offset + 1));
		(void)strncpy(new_line->op1, search_ptr, offset);
		new_line->op1[offset] = '\0';
	}

	/* skip single blank spaces (we need to halt on '\0') */
	search_ptr = end_ptr;
	while(*search_ptr == ' ') {
		search_ptr++;
	}

	/* op2 */
	new_line->op2 = NULL;
	/* if we haven't hit newline or comment delim, expect op2 */
	if(*search_ptr != '#' && *search_ptr != '\0') {
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
		new_line->op2 = malloc(sizeof(char) * (offset + 1));
		(void)strncpy(new_line->op2, search_ptr, offset);
		new_line->op2[offset] = '\0';
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
		free(search_ptr);
		search_ptr = next_ptr;
	}
}

void print_parsed_line(struct parsed_line *line)
{
	(void)printf("Label: %s\n", line->label);
	(void)printf("Instr: %s\n", line->instruction);
	(void)printf("Op1: %s\n", line->op1);
	(void)printf("Op2: %s\n", line->op2);
	(void)printf("\n");
}
