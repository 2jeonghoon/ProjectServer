#include "define.h"

#include "foodlist.h"
#include "table.h"

void processExit();
void setProcess();

int main(){

	char path[100] = PATH;

	int fd, fd_h, length, length_hall, pagesize, pagesize_hall;
	FoodList* addr;
	Table* addr_hall;

	FoodList* foodlist;
	Table* hall;
	foodlist = (FoodList*)malloc(sizeof(FoodList));
	if(foodlist == NULL){
		printf("struct error\n");
	}
	hall = (Table*)malloc(sizeof(FoodList));
	if(hall == NULL){
		printf("struct error\n");
	}
	
	pagesize = sizeof(FoodList);
	pagesize_hall = sizeof(Table);

	// file open
	if((fd = open("test.txt", O_RDWR | O_CREAT|O_TRUNC, 0666)) == -1)
		printf("fd error\n");
	if((fd_h = open("hall.txt", O_RDWR | O_CREAT|O_TRUNC, 0666)) == -1)
		printf("fd_h error\n");

	length = 1 * pagesize;
	length_hall = 1 * pagesize_hall;
	
	// size change
	if(ftruncate(fd, (off_t)length) == -1){
		printf("truncate error\n");
	}	
	if(ftruncate(fd_h, (off_t)length_hall) == -1){
		printf("hall truncate error\n");
	}


	// mmap
	addr = (FoodList*)mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);
	if(addr == MAP_FAILED)
		printf("mmap error\n");
	addr_hall = (Table*)mmap(NULL, length_hall, PROT_READ|PROT_WRITE, MAP_SHARED, fd_h, (off_t)0);
	if(addr_hall == MAP_FAILED)
		printf("mmap error\n");

	int serving_pid = fork();
	if(serving_pid == 0){
		strcat(path, "serving");
		execlp(path, "serving", NULL);
		printf("serving execlp error\n");
	}
	int clean_pid = fork();
	if(clean_pid == 0){
		strcat(path, "clean");
		execlp(path, "clean", NULL);
		printf("clean execlp error\n");
	}

	sleep(4);
	printf("\n---hall process creat---\n");
	init_table(addr_hall, addr->hall);


	int hall_index = 0;
	int hall_pid = 0;

	//printf("hall pid : %d\n", getpid());
	//printf("hall ppid : %d\n", getppid());
	signal(SIGUSR2, setProcess); //setProcess
	signal(SIGUSR1, processExit);
	while(1){
		addr_hall->input = addr->input;
	//	if(addr->input == 0){
	//		addr_hall->input = addr->input;
	//		printf("---hall input exit---\n");
	//		break;
	//	}
		if(addr->input == 3){
			print_table(addr_hall);
			addr->input = 999;
		}
	}

	close(fd);

	printf("\n---hall process exit---\n");

	return 0;
}

void processExit(int signo){
//	addr_hall->input = addr->input;
	printf("===hall signal exit===\n");
	exit(0);
}

void setProcess(){
	kill(getppid(), SIGUSR2);
}
