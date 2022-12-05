#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define TRUE 1
#define FALSE 0

#define INGREDIENT_TIME 5
#define GASRANGE_TIME 5
#define SETFOOD_TIME 5
#define SERVING_TIME 5
#define EATING_TIME 5
#define CLEAN_TIME 5
