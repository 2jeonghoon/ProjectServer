#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT_SHMIP 131118
#define KITCHEN_SHMIP 131130
#define ORDERLIST_SHMIP 131122
#define GASRANGELIST_SHMIP 131123
#define SETFOODLIST_SHMIP 131126

#define GASRANGE_COUNT 6

#define ORDER 10001
#define EXIT 10000

#define TRUE 1
#define FALSE 0
