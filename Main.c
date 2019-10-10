#define _POSIX_SOURCE
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <math.h>
#define PROCESSES_AVAILABLE 5
#define work_unit_size 50
int Work_by_Process[5]={25,10,5,15,20};
int curThread;
int curSortedPos;
int sorted_copy[PROCESSES_AVAILABLE];
/*
The previous definitions need to be configured by process so that each process has different amout of work
The previous need to be defined by text file
The prvious need to be set dinamically to N process
*/
sigjmp_buf mark[PROCESSES_AVAILABLE];
void FCFS_Scheduler_Execution();
void FCFS_Scheduler_Selection();
void FCFS_Scheduler_aux();
void FCFS_Scheduler();
void SJF_Scheduler_Execution();
void SJF_Scheduler_Selection();
void SJF_Scheduler_aux();
void SJF_Scheduler();
//float Calculate_Pi();
long double Calculate_Pi();
void sort();
int main()
{
	FCFS_Scheduler();
	SJF_Scheduler();
}
void FCFS_Scheduler(){
	printf("Started FCFS selection, this algorithm will execute linearly the processes\n");
	curThread=0; // FCFS always starts with the first job
	while(curThread<PROCESSES_AVAILABLE){
		FCFS_Scheduler_aux();
	}
}
void FCFS_Scheduler_aux(){

	if (sigsetjmp(mark[curThread],1) != 0) {
		FCFS_Scheduler_Selection();
		return;
	}
	FCFS_Scheduler_Execution();

}
void FCFS_Scheduler_Execution()
{
	//Calculate_Pi();

	unsigned int n = 1000000000;
	long double result = 0;

	result = Calculate_Pi(n);

	printf("terminos = %u, aproximacion = %Lf\n", n, result );

	printf("Current Thread %d\n",curThread);
	siglongjmp(mark[curThread], -1);
}

/*
FCFS doesn't require an specific algorithm selection
*/
void FCFS_Scheduler_Selection()
{
	printf("siglongjmp() has been called, a new thread is going to be selected\n");
	curThread++;
}

/*float Calculate_Pi(){

	int i,j;
	float result=1.0;
	printf("Pi result is %f\n",2*result);
	//Needs clarification since there are singificant issue if we want to calculate arcsin taylor series
	return 2*result;
}*/

long double Calculate_Pi(unsigned int terminos) {
    long double ans = 4;

    for (unsigned int i = 1; i <= terminos; i++) {
      ans += (4*pow(-1,i))/(2*i+1);
    }
    return ans;
}



void SJF_Scheduler(){
	curSortedPos=0;
	printf("Started SJF selection, this algorithm will execute linearly the processes in order of which takes less to execute\n");
	printf("Sorting the job sizes\n");
	sort();
	printf("Selecting next job\n");
	while(curSortedPos<PROCESSES_AVAILABLE){
		curThread=searchposition(sorted_copy[curSortedPos] ,Work_by_Process,PROCESSES_AVAILABLE);
		SJF_Scheduler_aux();
	}
}
void SJF_Scheduler_aux(){

	if (sigsetjmp(mark[curThread],1) != 0) {
		SJF_Scheduler_Selection();
		return;
	}
	SJF_Scheduler_Execution();

}
void SJF_Scheduler_Execution()
{
	//Calculate_Pi();

	unsigned int n = 1000000000;
	long double result = 0;

	result = Calculate_Pi(n);

	printf("terminos = %u, aproximacion = %Lf\n", n, result );

	printf("Current Thread %d\n",curThread);
	siglongjmp(mark[curThread], -1);
}

/*
SJF requires to take a look into the sorted list and decide which is the next process to execute
*/
void SJF_Scheduler_Selection()
{
	printf("siglongjmp() has been called, a new thread is going to be selected\n");
	//scheduler moves to the next shortest job
	curSortedPos++;
}

/*
Call to srot algorithm
*/

// Driver program to test above functions
void sort()
{
	memcpy(sorted_copy, Work_by_Process, sizeof(sorted_copy));
	int n = sizeof(sorted_copy)/sizeof(sorted_copy[0]);
	quickSort(sorted_copy, 0, n-1);
	printf("Sorted array: n");
	printArray(sorted_copy, n);
	printArray(Work_by_Process, n);
}
