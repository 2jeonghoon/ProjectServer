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

	// gasRange Count
	int gasRangeCount = 0;

	while(1){
		if(*input == EXIT){
			printf("gasRange input : %d\n", *input);
			break;
		}
	
		//가스레인지를 모두 사용 중일 때
		if(gasRangeCount == GASRANGE_COUNT){
			printf("gasRange full\n");
			//wait
			while(gasRangeCount == GASRANGE_COUNT){}
		}
		else if(is_empty_queue(gasRangelist) == FALSE && gasRangeCount < GASRANGE_COUNT ){
			queue_pop(gasRangelist);
			int child = fork();
			gasRangeCount--;
			if(child == 0){
				printf("\n---gasRangelist pop---\n");
				sleep(10);
				queue_insert(setFoodlist);
				printf("\n---gasRangelist pop complete\n");
				return -1;
			}
		}
	}

	printf("\n---gasRange process exit\n");
		
	return 0;
}
