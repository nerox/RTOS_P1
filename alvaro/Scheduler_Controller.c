#include "Controller.h"
#include "Scheduler.h"
#include "Deployer.h"
#include "Lottery.h"
#include "Lectura_json.h"
#include "Round_Robin.h"
#include "Quick_Sort.h"
#include "interfaz.h"


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

	parse_Data_From_File();
	availableTreads=0;
	priorityqueue_pos=0;
	sorted_Work_by_Process= malloc(PROCESSES_AVAILABLE * sizeof(int));
	sorted_Arrival_Time_by_Process= malloc(PROCESSES_AVAILABLE * sizeof(int));
       	process_list = malloc(PROCESSES_AVAILABLE * sizeof(my_pthreadpcb));
	int i;
	for (i=0;i++;i<PROCESSES_AVAILABLE){
		process_list[i].status=0;
	}
}
void Start_Scheduler()
{
	start_clock();
	sort(Arrival_Time_by_Process,sorted_Arrival_Time_by_Process,PROCESSES_AVAILABLE);
	switch (algorithm)
	{
	case 0: // code to be executed if n = 0;
		printf("LS\n");
		Lottery_Scheduler();
		break;
	case 1: // code to be executed if n = 1;
		printf("FCFS\n");
		FCFS_Scheduler();
		break;
	case 2: // code to be executed if n = 2;
		printf("RR\n");
		Round_Robin();
		break;
	default: // code to be executed if n doesn't match any cases
		printf("Unknow option selected please use RR,LS or FCFS as inputs");
		break;
	}
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

	Calculate_Pi(n);


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


void Calculate_Pi(unsigned int n) {

    update_progress_var.PI_value = 4.0;
    uint terminos = update_progress_var.terminos;
    printf("%0.3f\n",update_progress_var.PI_value );

    for (uint i = 1; i <= n; i++) {
      sprintf(path, "%d", curThread);
      update_progress_var.path = path;
      update_progress_var.status = "Active";//g_string_new (test);
      update_progress_var.PI_value += (4*pow(-1,i))/(2*i+1);
      update_progress_var.progress = 100*((double)i/(double)n);
    }
	process_list[curThread].status=2;
    	update_progress_var.status = "Finished";//g_string_new (test);

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
