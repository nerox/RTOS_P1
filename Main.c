#include "Controller.h"
#include "Scheduler.h"
#include "Deployer.h"
#include "Lottery.h"
int verify_pending_process(){
	int i;
	for(i=0;i<PROCESSES_AVAILABLE;i++){
		if (process_list[i].status!=2){
			return 1;
		}
	}
	return 0;
}
void start_Structures(){
	Work_by_Process[0]=500000;
	Work_by_Process[1]=250000;
	Work_by_Process[2]=1000000;
	Work_by_Process[3]=2500000;
	Work_by_Process[4]=2500000;
	Arrival_Time_by_Process[0]=4;
	Arrival_Time_by_Process[1]=0;
	Arrival_Time_by_Process[2]=1;
	Arrival_Time_by_Process[3]=2;
	Arrival_Time_by_Process[4]=3;
	Tickets_by_Process[0]=25;
	Tickets_by_Process[1]=50;
	Tickets_by_Process[2]=75;
	Tickets_by_Process[3]=100;
	Tickets_by_Process[4]=125;
	Quantum=100000;
	availableTreads=0;
	priorityqueue_pos=0;
       	process_list = malloc(PROCESSES_AVAILABLE * sizeof(my_pthreadpcb));
	int i;
	for (i=0;i++;i<PROCESSES_AVAILABLE){
		process_list[i].status=0;
	}
}
int main()
{
	start_Structures();
	start_clock();
	sort(Arrival_Time_by_Process,sorted_Arrival_Time_by_Process,PROCESSES_AVAILABLE);
	//FCFS_Scheduler();
	//SJF_Scheduler();
	Lottery_Scheduler();
}
void FCFS_Scheduler(){
	printf("Started FCFS selection, this algorithm will execute linearly the processes\n");
        address_t pc = (address_t)FCFS_Scheduler_Execution;
	while(verify_pending_process()){

		deployer(pc);
		curThread=searchposition(sorted_Arrival_Time_by_Process[priorityqueue_pos] ,Arrival_Time_by_Process,PROCESSES_AVAILABLE); // FCFS always starts with the first job
		if(process_list[curThread].status==1){
			FCFS_Scheduler_aux();
		}
		else if (process_list[curThread].status==2){
			Arrival_Time_by_Process[curThread]--;
		}
		else{
		}
	}
}
void FCFS_Scheduler_aux(){

	if (sigsetjmp(process_list[curThread].env,1) != 0) {
		FCFS_Scheduler_Selection();
		return;
	}
	FCFS_Scheduler_Execution();

}
void FCFS_Scheduler_Execution()
{
	unsigned int n = work_unit_size*Work_by_Process[curThread];
	long double result = 0;

	result = Calculate_Pi(n);

	printf("terminos = %u, aproximacion = %Lf\n", n, result );

	printf("Current Thread %d\n",curThread);
	process_list[curThread].status=2;
	printf("siglongjmp() has been called, a new thread is going to be selected\n");
	siglongjmp(process_list[curThread].env, -1);
}

/*
FCFS doesn't require an specific algorithm selection
*/
void FCFS_Scheduler_Selection()
{
	priorityqueue_pos++;
}


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
	sort(Work_by_Process,sorted_Work_by_Process,PROCESSES_AVAILABLE);
	printf("Selecting next job\n");
	while(curSortedPos<PROCESSES_AVAILABLE){
		curThread=searchposition(sorted_Work_by_Process[curSortedPos] ,Work_by_Process,PROCESSES_AVAILABLE);
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

	unsigned int n = work_unit_size*Work_by_Process[curThread];
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
Call to sort algorithm
*/

// Driver program to test above functions
void sort(int array[], int *sortedarray,int size)
{
	memcpy(sortedarray, array, size*sizeof(int));
	int n = size;
	quickSort(sortedarray, 0, n-1);
	printf("Sorted array: n");
	printArray(sortedarray, n);
	printArray(array, n);


}
