#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "foodlist.h"
#include "table.h"

int main(int argc, char* argv[]){

	if(argc != 3){
		printf("./main kitchen_num hall_num\n");
		return 0;
	}
	int kitchen = atoi(argv[1]);
	int hall = atoi(argv[2]);


	char path[100] = "/home/g_201911180/project/mmap/";


	int fd, length, pagesize;
	FoodList* addr;
	caddr_t addr2;

	FoodList* foodlist;
	foodlist = (FoodList*)malloc(sizeof(FoodList));
	if(foodlist == NULL){
		printf("struct error\n");
	}
	else{
		//init_foodlist(foodlist);
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

	close(fd);

	//	printf("addr : %d\n", foodlist);

	//print_foodlist(addr);

	// ingredient process
	int ingredient_pid = fork();
	if(ingredient_pid == 0){
		strcat(path, "ingredient");
		execlp(path, "ingredient", NULL);
		printf("ingredient execlp error\n");
	}
	int gasRange_pid = fork();
	if(gasRange_pid == 0){
		strcat(path, "gasRange");
		execlp(path, "gasRange", NULL);
		printf("gasRange execlp error\n");
	}
	int setFood_pid = fork();
	if(setFood_pid == 0){
		strcat(path, "setFood");
		execlp(path, "setFood", NULL);
		printf("setFood execlp error\n");
	}

	//hall
	int hall_pid = fork();
	if(hall_pid == 0){
		strcat(path, "hall");
		execlp(path, "hall", NULL);
		printf("hall execlp error\n");
	}

	sleep(1);
	init_foodlist(addr, kitchen, hall);	
	
	printf("addr->input : %d\n", addr->input);

	while(1){
		printf("order :1, foodlist : 2, delet_foodlist : 3, print_hall : 4,  msync : 9, exit :0 >> ");
		scanf("%d", &(addr->input));
		switch(addr->input){
			case 1:
				insert_order(addr);
				break;
			case 2:
				print_foodlist(addr);
				break;
			case 3:
				delete_foodlist(addr);
				break;
			case 9:
				msync(addr, length,MS_SYNC);
				break;
			case 0:
				printf("main process exit\n");
				exit(0);
		}
		if(msync(addr, length, MS_SYNC) == -1){
			printf("Could not sysnc\n");
		}  

	}


	printf("main process exit\n");

	return 0;
}
