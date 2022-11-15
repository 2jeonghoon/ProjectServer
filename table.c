#include "table.h"

void init_table(Table* table, int hall){
	printf("\n===init_table===\n");
	table->size = 10;
	table->index = 0;
	table->delete_index = 0;
	table->input = 999;
	table->hall = hall;
	for(int i = 0; i < table->size; i++){
		table->list[i] = 0;
	}
}

void insert_table(Table* table){
	if((table->index + 1) % table->size == table->delete_index){
		printf("table is full!!\n");
	}else{
		table->list[table->index] = 1;
		table->index = (table->index+1) % table->size;
	}
}

void delete_table(Table* table){
	if(table->index == table->delete_index){
		printf("table is empty!!\n");
	}else{
		table->list[table->delete_index] = 0;
		table->index = (table->index+1) % table->size;
	}
}

void print_table(Table* table){
	printf("\n===print_table===\n");
	printf("table->size :%d\n", table->size);
	printf("table->hall :%d\n", table->hall);
	printf("table->index : %d\n", table->index);
	printf("table->delete_index :%d\n", table->delete_index);
	printf("hall : %d\n", table->hall);

	for(int i = 0; i < table->size; i++){
		printf("[%d] : %d\n", i, table->list[i]);
	}
}
