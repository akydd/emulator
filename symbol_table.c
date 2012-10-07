/*
 * ============================================================================
 *
 *       Filename:  symbol_table.c
 *
 *    Description:  Implementation of the symbol table
 *
 *        Version:  1.0
 *        Created:  12-09-23 07:25:43 PM
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
#include "symbol_table.h"

void add_symbol(char *key, int value)
{
	/* allocated mem */
	struct entry *new_entry = malloc(sizeof(struct entry));
	new_entry->next = NULL;
	new_entry->key = malloc(sizeof(char) * (strlen(key) + 1));

	/* copy in key & value */
	(void)strcpy(new_entry->key, key);
	new_entry->value = value;

	/* add new entry to head of table */
	if (symbol_table != NULL) {
		new_entry->next = symbol_table;
	}
	symbol_table = new_entry;
}

int find_value(char *key)
{
	struct entry *search_ptr = symbol_table;
	while(search_ptr != NULL && (strcmp(search_ptr->key, key) != 0)) {
		search_ptr = search_ptr->next;
	}

	if (search_ptr == NULL) {
		return -1;
	}

	return search_ptr->value;
}

void delete_symbol_table()
{
	struct entry *search_ptr = symbol_table;
	struct entry *next_ptr;

	while(search_ptr != NULL) {
		next_ptr = search_ptr->next;
		free(search_ptr->key);
		free(search_ptr);
		search_ptr = next_ptr;
	}
}
