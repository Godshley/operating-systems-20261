#include <stdio.h>
#include "scheduler/scheduler.h"
#include "process/process.h"
#include "metrics/metrics.h"
#define NUM_PROCESSES 4
Process *finished_processes[NUM_PROCESSES] = {NULL};

int main()
{
    Scheduler *s = create_scheduler();
    Process *processes[NUM_PROCESSES];
    processes[0] = create_process(1,0,8);
    processes[1] = create_process(2,1,4);
    processes[2] = create_process(3,2,9);
    processes[3] = create_process(4,3,5);
    int finished = 0;

    while(finished < NUM_PROCESSES)
    {
	if(s->current_time > 0 && s->current_time % s->boost_interval == 0)
	{
    	priority_boost(s);
	}
        for(int i=0;i<NUM_PROCESSES;i++)
        {
            if(processes[i] != NULL &&
               processes[i]->arrival_time <= s->current_time)
            {
                add_process(s,processes[i]);
                processes[i] = NULL;
            }
        }

        Process *p = get_next_process(s);

        if(p != NULL)
        {
            run_process(s,p);

            if(p->remaining_time == 0)
		{
		finished_processes[p->pid - 1] = p;
                finished++;
		}
        }
        else
        {
            s->current_time++;
        }
    }
	printf("\n===== SCHEDULER METRICS =====\n");
	for(int i = 0; i < NUM_PROCESSES; i++)
	{
	if(finished_processes[i] != NULL)
		{
		print_metrics(finished_processes[i]);
		}
	}
	export_metrics_csv(finished_processes, NUM_PROCESSES);
	destroy_scheduler(s);

    return 0;
}
