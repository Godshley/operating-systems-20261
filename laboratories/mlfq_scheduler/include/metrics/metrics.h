#ifndef METRICS_H
#define METRICS_H
#include "process/process.h"

int calculate_response_time(Process *p);
int calculate_turnaround_time(Process *p);
int calculate_waiting_time(Process *p);
void print_metrics(Process *p);
void export_metrics_csv(Process *processes[], int count);
#endif
