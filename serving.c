#include "define.h"

#include "table.h"
#include "foodlist.h"

void foo(int signum){
	int status;
	while(waitpid(0, &status, WNOHANG) > 0){
		//printf("status : %d\n", status);
	}
}

// serving
int main(){

	char* path = PATH;

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

	sleep(6);
	printf("\n---serving process create---\n");	

	int serving_index = 0;
	int serving_pid = 0;

	signal(SIGCHLD, foo);
	while(1){
		if(addr_hall->input == 0){
			printf("---serving input exit---\n");
			break;
		}			

		if(addr->list[serving_index].ingredient == 1 && addr->list[serving_index].gasRange == 1
			&& addr->list[serving_index].setFood == 1 && addr_hall->hall > 0){
		
			addr_hall->hall--;			

			serving_pid = fork();
			if(serving_pid == 0){
				//printf("serving set!!\n");
				sleep(SERVING_TIME);
				delete_foodlist(addr);
				insert_table(addr_hall);
				//printf("\n---child serving exit---\n");
				addr_hall->hall++;
				exit(0);
			}
			serving_index = (serving_index + 1) % addr_hall->size;
		}
	}

	close(fd);

	printf("\n---serving process exit---\n");

	return 0;
}
