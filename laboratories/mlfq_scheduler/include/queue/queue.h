#ifndef QUEUE_H
#define QUEUE_H
#include "process/process.h"

typedef struct Node {
    Process *process;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

/* Ops de la queue */

Queue* create_queue();
void enqueue(Queue *q, Process *p);
Process* dequeue(Queue *q);
int is_empty(Queue *q);
void destroy_queue(Queue *q);
#endif
