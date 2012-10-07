/*
 * ============================================================================
 *
 *       Filename:  parsed_line_test.c
 *
 *    Description:  test cases for parsed_line.h
 *
 *        Version:  1.0
 *        Created:  12-10-06 06:40:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd (), akydd@ualberta.net
 *   Organization:  
 *
 * ============================================================================
 */
#include <stdlib.h>
#include "parsed_line.h"

struct parsed_line *parsed_lines = NULL;

int main(void)
{
	/*            123456789+ */
	char *str1 = "label1  instr\0"; /* label and instruction */
	char *str2 = "        instr\0"; /* instruction */
	char *str3 = "label3  instr op3\0"; /* label, instr, op1 */
	char *str4 = "        instr op4\0"; /*  instr, op1 */
	char *str5 = "label5  instr op5a,op5b\0";
	char *str6 = "label5  instr op5a, op5b \0";
	char *str7 = "        instr   op6a  ,  op6b  # comment \0";

	struct parsed_line *test1 = parse_line(str1);
	add_parsed_line(test1);
	struct parsed_line *test2 = parse_line(str2);
	add_parsed_line(test2);
	struct parsed_line *test3 = parse_line(str3);
	add_parsed_line(test3);
	struct parsed_line *test4 = parse_line(str4);
	add_parsed_line(test4);
	struct parsed_line *test5 = parse_line(str5);
	add_parsed_line(test5);
	struct parsed_line *test6 = parse_line(str6);
	add_parsed_line(test6);
	struct parsed_line *test7 = parse_line(str7);
	add_parsed_line(test7);

	print_parsed_line(test1);
	print_parsed_line(test2);
	print_parsed_line(test3);
	print_parsed_line(test4);
	print_parsed_line(test5);
	print_parsed_line(test6);
	print_parsed_line(test7);
	delete_parsed_lines();

	return(0);
}
