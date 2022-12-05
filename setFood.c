#include "define.h"

#include "foodlist.h"

void foo(int signum){
	int status;
	while(waitpid(0, &status, WNOHANG) > 0){
		//printf("status : %d\n", status);
	}

}

void processExit(int signo){
//	addr_hall->input = addr->input;
	printf("===setFood signal exit===\n");
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

	sleep(3);
	printf("\n---setFood process create---\n");

	int setFood_index = 0;
	int setFood_pid = 0;
	signal(SIGCHLD, foo);
	signal(SIGUSR1, processExit);
	while(1){
		if(addr->input == 0){
			printf("---setFood input exit---\n");
			break;
		}

		if(addr->list[setFood_index].ingredient == 1 && addr->list[setFood_index].gasRange == 1
			&& addr->list[setFood_index].setFood == 0 && addr->kitchen > 0){
		
			addr->kitchen--;			

			setFood_pid = fork();
			if(setFood_pid == 0){
				//printf("setFood set!!\n");
				sleep(SETFOOD_TIME);
				addr->list[setFood_index].setFood = 1;
				//printf("---child setFood exit---\n");
				addr->kitchen++;
				exit(0);
			}
			setFood_index = (setFood_index + 1) % addr->size;
		}
	}
	printf("---setFood process exit---\n");

	return 0;
}
