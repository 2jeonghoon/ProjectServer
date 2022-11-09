#include "define.h"
#include "queue.h"

int main(){

	printf("\n---ingredient process on---\n");

	Queue* orderlist_addr = (Queue*)shmat(ORDERLIST_SHMIP, NULL, 0);
	Queue* orderlist = orderlist_addr;

	Queue* gasRangelist_addr = (Queue*)shmat(GASRANGELIST_SHMIP, NULL, 0);
	Queue* gasRangelist = gasRangelist_addr;

	int *input_addr = (int*)shmat(INPUT_SHMIP, NULL, 0);
	int *input = input_addr;

	int *kitchen_addr = (int*)shmat(KITCHEN_SHMIP, NULL, 0);
	int *kitchen = kitchen_addr;

	while(1){
		if(*input == EXIT){
			printf("ingredient input : %d\n", *input);
			break;
		}
		if(is_empty_queue(orderlist) == FALSE && *kitchen > 0){
			queue_pop(orderlist);
			int child = fork();
			if(child == 0){
				printf("---ingredient child create---\n");
				//Lock
				*kitchen = *kitchen - 1;
				sleep(5);
				//Lock
				queue_insert(gasRangelist);
				printf("\n---ingredient pop complete\n");
				//Lock
				*kitchen = *kitchen + 1;
				return -1;
			}
		}
	}

	printf("\n---ingredient process exit\n");
		
	return 0;
}
