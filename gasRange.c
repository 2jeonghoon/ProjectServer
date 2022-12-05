#include "define.h"

#include "foodlist.h"


int gasRange_count = 0;
int gasRange_amount = 8;

void foo(int signum){
	int status;
	while(waitpid(0, &status, WNOHANG) > 0){
		gasRange_count--;
		//printf("status : %d\n", status);
	}
}

void processExit(int signo){
//	addr_hall->input = addr->input;
	printf("===gasRange signal exit===\n");
	exit(0);

}
int main(){

	char* path = "/home/g_201911180/project/mmap/";

	int fd, length, pagesize;
	FoodList* addr;
	caddr_t addr2;

	FoodList* foodlist;
	foodlist = (FoodList*)malloc(sizeof(FoodList));
	if(foodlist == NULL){
		printf("struct error\n");
	}
	
	pagesize = sizeof(FoodList);

	// file open
	if((fd = open("test.txt", O_RDWR | O_CREAT|O_TRUNC, 0666)) == -1)
		printf("fd error\n");

	length = 1 * pagesize;
	
	// size change
	if(ftruncate(fd, (off_t)length) == -1){
		printf("truncate error\n");
	}	

	// mmap
	addr = (FoodList*)mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);
	if(addr == MAP_FAILED)
		printf("mmap error\n");

	sleep(2);
	printf("\n---gasRange process create---\n");

	int gasRange_index = 0;
	int gasRange_pid = 0;

	signal(SIGCHLD, foo);
	signal(SIGUSR1, processExit);
	while(1){
		if(addr->input == 0){
			printf("---gasRange input exit---\n");
			print_foodlist(addr);
			break;
		}

		if(addr->list[gasRange_index].ingredient == 1 && addr->list[gasRange_index].gasRange == 0
			&& gasRange_count < gasRange_amount){
			gasRange_count++;
			gasRange_pid = fork();
			if(gasRange_pid == 0){
				//printf("gasRange set!!\n");
				sleep(GASRANGE_TIME);
				addr->list[gasRange_index].gasRange = 1;
				//printf("child gasRange exit\n");
				exit(0);
			}
			gasRange_index = (gasRange_index + 1) % addr->size;
		}
	}
	printf("---gasRange process exit---\n");
	return 0;
}	


