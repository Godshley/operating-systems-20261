#ifndef PROCESS_H
#define PROCESS_H

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int finish_time;
    int first_response_time;
    int current_queue;
} Process;


/* Funciones para los procesos */

Process* create_process(int pid, int arrival, int burst);
void destroy_process(Process *p);
void print_process(Process *p);
#endif
