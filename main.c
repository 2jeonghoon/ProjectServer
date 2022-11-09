#include "define.h"
#include "queue.h"

int main(int argc, char* argv[]){
	char* path = "/home/g_201911180/test1";

	if(argc != 3){
		printf("./main kitchenNum hallNum\n");
		return 0;
	}

	//kitchen init	
	int* kitchen_addr = (int*)shmat(KITCHEN_SHMIP, NULL, 0);
	int* kitchen = kitchen_addr;
	*kitchen = atoi(argv[1]);

	//orderlist shm
	Queue* orderlist_addr = (Queue*)shmat(ORDERLIST_SHMIP, NULL, 0);
	Queue* orderlist = orderlist_addr;	
	init_queue(orderlist, 10);

	//gasRangelist shm
	Queue* gasRangelist_addr = (Queue*)shmat(GASRANGELIST_SHMIP, NULL, 0);
	Queue* gasRangelist = gasRangelist_addr;	
	init_queue(gasRangelist, 10);

	//setFoodlist shm
	Queue* setFoodlist_addr = (Queue*)shmat(SETFOODLIST_SHMIP, NULL, 0);
	Queue* setFoodlist = setFoodlist_addr;	
	init_queue(setFoodlist, 10);

	//input init
	int* input_addr = (int*)shmat(INPUT_SHMIP, NULL, 0);
	int* input = input_addr;
	*input = 999;

	int ingredient_pid = fork();
	if(ingredient_pid == 0){
		path = "/home/g_201911180/test1/ingredient";
		execlp(path, "ingredient", NULL);
		printf("ingredient process fail\n");
		return -1;
	}

	int gasRange_pid = fork();
	if(gasRange_pid == 0){
		path = "/home/g_201911180/test1/gasRange";
		execlp(path, "gasRange", NULL);
		printf("gasRange process fail\n");
		return -1;
	}

	int setFood_pid = fork();
	if(setFood_pid == 0){
		path = "/home/g_201911180/test1/setFood";
		execlp(path, "setFood", NULL);
		printf("setFood process fail\n");
		return -1;
	}

	printf("---kitchen : %d, hall : %d---\n", *kitchen, atoi(argv[2]));

	while(1){
	
		printf("order : 1, orderprint : 2, gasRangeprint : 3, setFoodprint : 4, restaurant : 9, exit : 0 >> ");
		scanf("%d", input);

		switch(*input){

			case 1:
				*input = 1;
				queue_insert(orderlist);
				printf("\n---order---\n");
				break;
			case 2:
				queue_print(orderlist);
				break;
			case 3:
				queue_print(gasRangelist);
				break;
			case 4:
				queue_print(setFoodlist);
				break;
			case 9:
				printf("---kitchen : %d, hall : %d---\n", *kitchen, atoi(argv[2]));
				break;
			case 0:
				*input = EXIT;
				printf("\n---exit---\n");
				return 0;
		}		

	
	}
	free(input);
	free(orderlist);
	free(gasRangelist);
	free(setFoodlist);

	return 0;
}
