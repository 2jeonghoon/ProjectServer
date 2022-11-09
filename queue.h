#include "define.h"

typedef struct Queue {
	int list[10];
	int size;
	int front;
	int rear;
}Queue;

void init_queue(Queue* q, int size);

int is_full_queue(Queue* q);

int is_empty_queue(Queue* q);

void queue_insert(Queue* q);

int  queue_pop(Queue* q);

void queue_print(Queue* q);
