#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <math.h>

#define PROCESSES_AVAILABLE 5
#define work_unit_size 50
#define STACK_SIZE 400096
typedef struct{
   int thread_id;
   int status;
   sigjmp_buf    env;
   char stack[STACK_SIZE];

}my_pthreadpcb;

my_pthreadpcb *process_list;
int Work_by_Process[PROCESSES_AVAILABLE];
int Arrival_Time_by_Process[PROCESSES_AVAILABLE];
int Process_State[PROCESSES_AVAILABLE];
int Tickets_by_Process[PROCESSES_AVAILABLE];
int availableTreads;
int curThread;
int curSortedPos;
int sorted_Work_by_Process[PROCESSES_AVAILABLE];
int sorted_Arrival_Time_by_Process[PROCESSES_AVAILABLE];
sigjmp_buf mark[PROCESSES_AVAILABLE];
int priorityqueue_pos;
int Quantum;
/*
The previous definitions need to be configured by process so that each process has different amout of work
The previous need to be defined by text file
The prvious need to be set dinamically to N process
*/

void FCFS_Scheduler_Execution();
void FCFS_Scheduler_Selection();
void FCFS_Scheduler_aux();
void FCFS_Scheduler();
void SJF_Scheduler_Execution();
void SJF_Scheduler_Selection();
void SJF_Scheduler_aux();
void SJF_Scheduler();
long double Calculate_Pi();
void sort(int array[], int *sortedarray,int size);
void start_Structures();
int verify_pending_process();
#endif
