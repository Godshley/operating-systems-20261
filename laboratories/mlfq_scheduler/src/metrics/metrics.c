#include <stdio.h>
#include "metrics/metrics.h"

int calculate_response_time(Process *p)
{
    return p->start_time - p->arrival_time;
}

int calculate_turnaround_time(Process *p)
{
    return p->finish_time - p->arrival_time;
}

int calculate_waiting_time(Process *p)
{
    return calculate_turnaround_time(p) - p->burst_time;
}

void print_metrics(Process *p)
{

    int response = calculate_response_time(p);
    int turnaround = calculate_turnaround_time(p);
    int waiting = calculate_waiting_time(p);
    printf("\nMetrics for process %d\n", p->pid);
    printf("Response Time: %d\n", response);
    printf("Turnaround Time: %d\n", turnaround);
    printf("Waiting Time: %d\n", waiting);
}
void export_metrics_csv(Process *processes[], int count)
{
    FILE *file = fopen("assets/results.csv", "w");

    if(file == NULL)
    {
        printf("Error creating results.csv\n");
        return;
    }

    fprintf(file,"PID,Arrival,Burst,Start,Finish,Response,Turnaround,Waiting\n");

    for(int i=0;i<count;i++)
    {
        Process *p = processes[i];

        int response = calculate_response_time(p);
        int turnaround = calculate_turnaround_time(p);
        int waiting = calculate_waiting_time(p);
        fprintf(file,"%d,%d,%d,%d,%d,%d,%d,%d\n",
                p->pid,
                p->arrival_time,
                p->burst_time,
                p->start_time,
                p->finish_time,
                response,
                turnaround,
                waiting);
    }

    fclose(file);

    printf("\nResults exported to assets/results.csv\n");
}
