#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "queue/queue.h"
#include "process/process.h"

typedef struct {
    Queue *Q0;
    Queue *Q1;
    Queue *Q2;
    int quantum_Q0;
    int quantum_Q1;
    int quantum_Q2;
    int current_time;
    int boost_interval;
} Scheduler;

/* Funciones del scheduler */

Scheduler* create_scheduler();
void destroy_scheduler(Scheduler *s);
void add_process(Scheduler *s, Process *p);
Process* get_next_process(Scheduler *s);
void run_process(Scheduler *s, Process *p);
void priority_boost(Scheduler *s);
#endif
