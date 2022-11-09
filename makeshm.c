#include "define.h"
#include "queue.h"

int main(){

	//input shm
	if((void*)shmat(INPUT_SHMIP, NULL, 0) == (void*)-1){
		int input_shmip = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0644);	
		printf("make Input_shmip = %d\n", input_shmip);
	}

	//kitchen shm
	if((void*)shmat(KITCHEN_SHMIP, NULL, 0) == (void*)-1){
		int kitchen_shmip = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0644);	
		printf("make kitchen_shmip = %d\n", kitchen_shmip);
	}
	

	//orderlist shm
	if((void*)shmat(ORDERLIST_SHMIP, NULL, 0) == (void*)-1){
		int orderlist_shmip = shmget(IPC_PRIVATE, sizeof(Queue), IPC_CREAT|0644);
		printf("make orderlist_shmip = %d\n", orderlist_shmip);
	}

	//gasRangelist shm
	if((void*)shmat(GASRANGELIST_SHMIP, NULL, 0) == (void*)-1){
		int gasRangelist_shmip = shmget(IPC_PRIVATE, sizeof(Queue), IPC_CREAT|0644);
		printf("make orderlist_shmip = %d\n", gasRangelist_shmip);
	}

	//setFoodlist shm
	if((void*)shmat(SETFOODLIST_SHMIP, NULL, 0) == (void*)-1){
		int setFoodlist_shmip = shmget(IPC_PRIVATE, sizeof(Queue), IPC_CREAT|0644);
		printf("make setFoodlist_shmip = %d\n", setFoodlist_shmip);
	}

	return 0;
}
