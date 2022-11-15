#include "foodlist.h"

void init_foodlist(FoodList* foodlist, int kitchen, int hall){
	foodlist->kitchen = kitchen;
	foodlist->hall = hall;
	foodlist->size = 10;
	foodlist->index = 0;
	foodlist->delete_index = 0;
	foodlist->input = 999;
	for(int i = 0; i < foodlist->size; i++){
		insert_foodlist(foodlist);
	}
}

int check_food(Food food){
	if(food.ingredient == -1){
		return TRUE;
	}
	printf("not order index\n");
	return FALSE;	
}

void insert_foodlist(FoodList* foodlist){
	Food* new_food = (Food*)malloc(sizeof(Food));
	init_food(new_food);
	foodlist->list[foodlist->index] = *new_food;
	foodlist->index = (foodlist->index + 1) % foodlist->size;
}

void delete_foodlist(FoodList* foodlist){
	if(foodlist->delete_index == foodlist->index){
		printf("foodlist empty!!\n");
		return;
	}
	init_food(&(foodlist->list[foodlist->delete_index]));
	foodlist->delete_index = (foodlist->delete_index + 1) % foodlist->size;

}


void insert_order(FoodList* foodlist){
	int index = foodlist->index;
	if((index+1) % foodlist->size == foodlist->delete_index){
		printf("===foodlist is full===\n");
		return;
	}
	if(check_food(foodlist->list[index]) == TRUE){
		printf("\n===insert_order===\n");
		foodlist->index = (foodlist->index + 1) % foodlist->size;
		foodlist->list[index].ingredient = 0;
		foodlist->list[index].gasRange = 0;
		foodlist->list[index].setFood = 0;
	}
}


void print_foodlist(FoodList* foodlist){
	printf("\n===print_foodlist===\n");
	printf("foodlist->size :%d\n", foodlist->size);
	printf("foodlist->index : %d\n", foodlist->index);
	printf("foodlist->delete_index :%d\n", foodlist->delete_index);
	printf("kitchen : %d\n", foodlist->kitchen);
	printf("hall : %d\n", foodlist->hall);

	for(int i = 0; i < foodlist->size; i++){
		printf("---[%d]---\n", i);
		printf("%d %d %d\n", foodlist->list[i].ingredient, foodlist->list[i].gasRange, foodlist->list[i].setFood);
	}
}
