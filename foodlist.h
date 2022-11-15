#include "define.h"
#include "food.h"

typedef struct FoodList{
	int kitchen;
	int hall;
	int input;
	Food list[10];
	int size;
	int index;
	int delete_index;
	
}FoodList;

void init_foodlist(FoodList* foodlist, int kitchen, int hall);

void insert_foodlist(FoodList* foodlist);

void delete_foodlist(FoodList* foodlist);

void insert_order(FoodList* foodlist);

void print_foodlist(FoodList* foodlist);
