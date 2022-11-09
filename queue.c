#include "queue.h"

void init_queue(Queue* q, int size) {
	q->front = 0;
	q->rear = 1;
	q->size = 10;
	//q->list = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < q->size; i++) {
		q->list[i] = 0;
	}
}

int is_full_queue(Queue* q) {
	if (q->rear == q->front) {
		return TRUE;
	}
	return FALSE;
}

int is_empty_queue(Queue* q) {
	if (q->front + 1 % q->size == q->rear) {
		return TRUE;
	}
	return FALSE;
}

void queue_insert(Queue* q) {
	if (is_full_queue(q)) {
		printf("queue is full\n");
		return;
	}
	q->list[q->rear] = 1;
	q->rear = (q->rear + 1) % (q->size);
}

int queue_pop(Queue* q) {
	if (is_empty_queue(q)) {
		printf("queue is empty\n");
		return FALSE;
	}
	q->front = (q->front + 1) % (q->size);
	q->list[q->front] = FALSE;
	return TRUE;
}

void queue_print(Queue* q) {
	int front = q->front;
	int rear = q->rear;
	printf("front : %d, rear : %d\n", front, rear);
	for (int i = 0; i < q->size; i++) {
		printf("list[%d] = %d\n", i, q->list[i]);
	}
}
