#include <stdio.h>
#include <stdlib.h>
#include "queue/queue.h"

Queue* create_queue()
{
    Queue *q = malloc(sizeof(Queue));

    if(q == NULL)
    {
        printf("Error allocating queue\n");
        return NULL;
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int is_empty(Queue *q)
{
    return q->front == NULL;
}

void enqueue(Queue *q, Process *p)
{
    Node *node = malloc(sizeof(Node));

    if(node == NULL)
    {
        printf("Error allocating node\n");
        return;
    }
    node->process = p;
    node->next = NULL;

    if(is_empty(q))
    {
        q->front = node;
        q->rear = node;
    }
    else
    {
        q->rear->next = node;
        q->rear = node;
    }
}
Process* dequeue(Queue *q)
{

    if(is_empty(q))
        return NULL;

    Node *temp = q->front;
    Process *p = temp->process;
    q->front = q->front->next;

    if(q->front == NULL)
        q->rear = NULL;

    free(temp);
    return p;
}

void destroy_queue(Queue *q)
{

    while(!is_empty(q))
    {
        dequeue(q);
    }

    free(q);
}
