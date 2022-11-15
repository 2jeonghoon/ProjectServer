#include "define.h"

#include "foodlist.h"

void foo(int signum){
	int status;
	while(waitpid(0, &status, WNOHANG) > 0){
		printf("status : %d\n", status);
	}
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

	sleep(1.5f);
	printf("\n---ingredient process creat---\n");

	int ingredient_index = 0;
	int ingredient_pid = 0;

	signal(SIGCHLD, foo);
	while(1){
		if(addr->input == 0){
			printf("addr->input : %d\n", addr->input);
			printf("---ingredient input exit---\n");
			break;
		}
			

		if(addr->list[ingredient_index].ingredient == 0 && addr->kitchen > 0){
		
			addr->kitchen--;			

			ingredient_pid = fork();
			if(ingredient_pid == 0){
				printf("ingredient set!!\n");
				sleep(INGREDIENT_TIME);
				addr->list[ingredient_index].ingredient = 1;
				printf("\n---child ingredient exit---\n");
				addr->kitchen++;
				exit(0);
			}
			ingredient_index = (ingredient_index + 1) % addr->size;
		}
	}

	close(fd);

	printf("\n---ingredient process exit---\n");

	return 0;
}
