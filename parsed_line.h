/*
 * ============================================================================
 *
 *       Filename:  parsed_line.h
 *
 *    Description:  Parser for the assembly language
 *
 *        Version:  1.0
 *        Created:  12-09-23 08:38:10 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd (), akydd@ualberta.net
 *   Organization:  
 *
 * ============================================================================
 */

struct parsed_line {
	char *label;
	char *instruction;
	char *op1;
	char *op2;
	int size;
	struct parsed_line *next;
};

extern struct parsed_line *parsed_lines;

struct parsed_line *parse_line(char *);

void add_parsed_line(struct parsed_line *);

void delete_parsed_lines();
