#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <math.h>


#define work_unit_size 50
#define STACK_SIZE 400096
typedef struct{
   int thread_id;
   int status;
   sigjmp_buf    env;
   char stack[STACK_SIZE];

}my_pthreadpcb;
char path[10];
int algorithm;
my_pthreadpcb *process_list;
int PROCESSES_AVAILABLE;
int *Work_by_Process;
int *Arrival_Time_by_Process;
int *Process_State;
int *Tickets_by_Process;
int *sorted_Work_by_Process;
int *sorted_Arrival_Time_by_Process;
int *progress_by_process;
float *calculated_pi_process;
int availableTreads;
int curThread;
int curSortedPos;

int priorityqueue_pos;
int Quantum;
/*
The previous definitions need to be configured by process so that each process has different amout of work
The previous need to be defined by text file
The prvious need to be set dinamically to N process
*/
void Start_Scheduler();
void FCFS_Scheduler_Execution();
void FCFS_Scheduler_Selection();
void FCFS_Scheduler_aux();
void FCFS_Scheduler();
void SJF_Scheduler_Execution();
void SJF_Scheduler_Selection();
void SJF_Scheduler_aux();
void SJF_Scheduler();
void Calculate_Pi();
void sort(int array[], int *sortedarray,int size);
void start_Structures();
int verify_pending_process();
#endif
