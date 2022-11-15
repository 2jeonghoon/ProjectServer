#include <string.h>
#include <stdio.h>

typedef struct Food{
	int ingredient;
	int gasRange;
	int setFood;
}Food;

void init_food(Food* food);

void print_food(Food* food);
