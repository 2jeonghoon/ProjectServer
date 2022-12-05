#include "define.h"

#include "table.h"

void foo(int signum){
	int status;
	while(waitpid(0, &status, WNOHANG) > 0){
		//printf("status : %d\n", status);
	}
}

void count_sales(FILE* fp, int sales_count){
	char str[100];
	fseek(fp, 0, SEEK_SET);
	sprintf(str, "%d", sales_count);
	fputs(str, fp);
}

// clean
int main(){

	char* path = "/home/g_201911180/project/mmap/";

	FILE* sales_list;
	int fd, fd_h, length, length_hall, pagesize, pagesize_hall;
	Table* addr_hall;

	Table* hall;
	hall = (Table*)malloc(sizeof(Table));
	if(hall == NULL){
		printf("struct error\n");
	}
	
	pagesize_hall = sizeof(Table);

	// file open
	if((fd_h = open("hall.txt", O_RDWR | O_CREAT|O_TRUNC, 0666)) == -1)
		printf("fd_h error\n");
	//판매기록을 저장할 파일 생성
	sales_list = fopen("salesList.txt", "w");

	length_hall = 1 * pagesize_hall;
	
	// size change
	if(ftruncate(fd_h, (off_t)length_hall) == -1){
		printf("hall truncate error\n");
	}

	// mmap
	addr_hall = (Table*)mmap(NULL, length_hall, PROT_READ|PROT_WRITE, MAP_SHARED, fd_h, (off_t)0);
	if(addr_hall == MAP_FAILED)
		printf("mmap error\n");

	sleep(7);
	printf("\n---clean process create---\n");	
	kill(getppid(), SIGUSR2);

	int clean_index =0;
	int clean_pid = 0;

	signal(SIGCHLD, foo);
	while(1){
		if(addr_hall->input == 0){
			printf("---clean input exit---\n");
			break;
		}			

		if(addr_hall->list[clean_index] == 1 && addr_hall->hall > 0){
			addr_hall->hall--;			
			clean_pid = fork();
			if(clean_pid == 0){
				//printf("clean set!!\n");
				sleep(CLEAN_TIME);
				delete_table(addr_hall);
				//printf("\n---child serving exit---\n");
				addr_hall->hall++;
				count_sales(sales_list, ++addr_hall->sales_count);
				exit(0);
			}
			clean_index = (clean_index + 1) % addr_hall->size;
		}
	}

	close(fd);

	printf("\n---clean process exit---\n");

	return 0;
}

