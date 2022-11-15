#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define INGREDIENT_TIME 10
#define GASRANGE_TIME 30
#define SETFOOD_TIME 10
#define SERVING_TIME 10
#define EATING_TIME 30
#define CLEAN_TIME 10
