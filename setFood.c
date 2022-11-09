#include "define.h"
#include "queue.h"

int main(){

	printf("\n---setFood process on---\n");

	Queue* setFoodlist_addr = (Queue*)shmat(SETFOODLIST_SHMIP, NULL, 0);
	Queue* setFoodlist = setFoodlist_addr;

	int *input_addr = (int*)shmat(INPUT_SHMIP, NULL, 0);
	int *input = input_addr;

	int *kitchen_addr = (int*)shmat(KITCHEN_SHMIP, NULL, 0);
	int *kitchen = kitchen_addr;

	while(1){
		if(*input == EXIT){
			printf("setFood input : %d\n", *input);
			break;
		}
		
		if(is_empty_queue(setFoodlist) == FALSE && *kitchen > 0){
			*kitchen = *kitchen - 1;
			printf("\n---setFood pop---\n");
			printf("pop : %d\n", queue_pop(setFoodlist));
			sleep(5);
			//queue_insert(setFoodlist);
			printf("\n---setFood pop complete\n");
			*kitchen = *kitchen + 1;
		}
	}

	printf("\n---setFood process exit\n");
		
	return 0;
}
