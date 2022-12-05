#include "food.h"

void init_food(Food* food){
	food->ingredient = -1;
	food->gasRange = -1;
	food->setFood = -1;

}

void print_food(Food* food){

	printf("\n === food print === \n");
	printf("ingredient : %d\n", food->ingredient);
	printf("gasRange : %d\n", food->gasRange);
	printf("setFood : %d\n", food->setFood);

}
