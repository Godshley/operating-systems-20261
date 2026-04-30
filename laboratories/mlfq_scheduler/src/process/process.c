#include <stdio.h>
#include <stdlib.h>
#include "process/process.h"

Process* create_process(int pid, int arrival, int burst){
    Process *p = malloc(sizeof(Process));
    if(p == NULL){
        printf("Error allocating memory for process\n");
        return NULL;
    }

    p->pid = pid;
    p->arrival_time = arrival;
    p->burst_time = burst;
    p->remaining_time = burst;
    p->start_time = -1;
    p->finish_time = -1;
    p->first_response_time = -1;
    p->current_queue = 0;
    return p;
}

void destroy_process(Process *p)
{
    if(p != NULL)
        free(p);
}

void print_process(Process *p)
{
    printf(
        "PID:%d Arrival:%d Burst:%d Remaining:%d Queue:%d\n",
        p->pid,
        p->arrival_time,
        p->burst_time,
        p->remaining_time,
        p->current_queue
    );
}
