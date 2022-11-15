#include "define.h"

typedef struct Table{
	int list[10];
	int size;
	int input;
	int index;
	int delete_index;
	int hall;
}Table;

void init_table(Table* table, int hall);

void insert_table(Table* table);

void delete_table(Table* table);

void print_table(Table* table);
