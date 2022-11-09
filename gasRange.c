#include "define.h"
#include "queue.h"

int main(){

	printf("\n---gasRange process on---\n");

	Queue* gasRangelist_addr = (Queue*)shmat(GASRANGELIST_SHMIP, NULL, 0);
	Queue* gasRangelist = gasRangelist_addr;

	Queue* setFoodlist_addr = (Queue*)shmat(SETFOODLIST_SHMIP, NULL, 0);
	Queue* setFoodlist = setFoodlist_addr;

	int *input_addr = (int*)shmat(INPUT_SHMIP, NULL, 0);
	int *input = input_addr;

	int *kitchen_addr = (int*)shmat(KITCHEN_SHMIP, NULL, 0);
	int *kitchen = kitchen_addr;

	while(1){
		if(*input == EXIT){
			printf("gasRange input : %d\n", *input);
			break;
		}
		
		if(is_empty_queue(gasRangelist) == FALSE && *kitchen > 0){
			printf("\n---gasRangelist pop---\n");
			printf("pop : %d\n", queue_pop(gasRangelist));
			sleep(10);
			queue_insert(setFoodlist);
			printf("\n---gasRangelist pop complete\n");
		}
	}

	printf("\n---gasRange process exit\n");
		
	return 0;
}
