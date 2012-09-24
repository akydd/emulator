/*
 * ============================================================================
 *
 *       Filename:  symbol_table.h
 *
 *    Description:  Symbol table is implemented as a linked list.
 *    		    Maps labels to memory addresses.
 *
 *        Version:  1.0
 *        Created:  12-09-23 07:18:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alan Kydd (), akydd@ualberta.net
 *   Organization:  
 *
 * ============================================================================
 */

struct entry {
	char *key;
	int value;
	struct entry *next;
};

extern struct entry *symbol_table;

/*
 * Add a new key-value pair to the head of the symbol table.
 * null chars are included in the data!
 */
void add(char *, int);

/*
 * Return the value for the key
 */
int find_value(char *);

/*
 * Free the allocated memory associated to the symbol table
 */
void delete_symbol_table();
