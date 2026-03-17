#include <stdio.h>
#include <stdlib.h>
#include "scheduler/scheduler.h"

Scheduler* create_scheduler()
{
    Scheduler *s = malloc(sizeof(Scheduler));

    if(s == NULL)
    {
        printf("Error allocating scheduler\n");
        return NULL;
    }

    s->Q0 = create_queue();
    s->Q1 = create_queue();
    s->Q2 = create_queue();
    s->quantum_Q0 = 2;
    s->quantum_Q1 = 4;
    s->quantum_Q2 = 8;
    s->current_time = 0;
    s->boost_interval = 20;
    return s;
}

void destroy_scheduler(Scheduler *s)
{
    destroy_queue(s->Q0);
    destroy_queue(s->Q1);
    destroy_queue(s->Q2);
    free(s);
}

void add_process(Scheduler *s, Process *p)
{
    enqueue(s->Q0,p);
}

Process* get_next_process(Scheduler *s)
{

    if(!is_empty(s->Q0))
        return dequeue(s->Q0);

    if(!is_empty(s->Q1))
        return dequeue(s->Q1);

    if(!is_empty(s->Q2))
        return dequeue(s->Q2);

    return NULL;
}

void run_process(Scheduler *s, Process *p)
{

    int quantum;

    if(p->current_queue == 0)
        quantum = s->quantum_Q0;
    else if(p->current_queue == 1)
        quantum = s->quantum_Q1;
    else
        quantum = s->quantum_Q2;

    if(p->start_time == -1)
    {
        p->start_time = s->current_time;
        p->first_response_time = s->current_time;
    }

    printf("\nRunning process %d in Q%d\n", p->pid, p->current_queue);
    int execution_time;

    if(p->remaining_time < quantum)
        execution_time = p->remaining_time;
    else
        execution_time = quantum;

    p->remaining_time -= execution_time;
    s->current_time += execution_time;

    if(p->remaining_time == 0)
    {
        p->finish_time = s->current_time;
        printf("Process %d finished at time %d\n",
        p->pid,
        p->finish_time);
    }
    else
    {

        if(p->current_queue < 2)
            p->current_queue++;

        printf("Process %d demoted to Q%d\n",
        p->pid,
        p->current_queue);

        if(p->current_queue == 0)
            enqueue(s->Q0,p);
        else if(p->current_queue == 1)
            enqueue(s->Q1,p);
        else
            enqueue(s->Q2,p);
    }
}

void priority_boost(Scheduler *s)
{

    printf("\n*** PRIORITY BOOST ACTIVATED ***\n");

    Process *p;

    while(!is_empty(s->Q1))
    {
        p = dequeue(s->Q1);
        p->current_queue = 0;
        enqueue(s->Q0,p);
    }

    while(!is_empty(s->Q2))
    {
        p = dequeue(s->Q2);
        p->current_queue = 0;
        enqueue(s->Q0,p);
    }
}
