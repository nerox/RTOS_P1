

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


