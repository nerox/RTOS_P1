#include "Round_Robin.h"

void Round_Robin_Execution()
{
	unsigned int n = work_unit_size*Work_by_Process[curThread];
	long double result = 0;

	long double ans = 4;

	for (unsigned int i = 1; i <= n; i++) {
		ans += (4*pow(-1,i))/(2*i+1);
		//printf("terminos resueltos = %u, aproximacion = %Lf en el hilo %d\n", i, ans,curThread );
	}


	printf("terminos = %u, aproximacion = %Lf en el hilo %d\n", n, ans,curThread );
	process_list[curThread].status=2;
	while (1) {
		//printf("holis%d\n",curThread);
	}

	
}

void select_thread_Round_Robin(){
	if (curThread+1<PROCESSES_AVAILABLE){
		selectThread(curThread+1);
	}
	else {
		selectThread(0);//Returns to the first position
	}
}
void selectThread(int position){
	int i;
	for (i=position;i<PROCESSES_AVAILABLE;i++){
		if (process_list[i].status==1){
			curThread=i;
			break;
		}
	}
}
void Round_Robin_aux()
{

	int ret_val = sigsetjmp(process_list[curThread].env,1);
	if (ret_val == 1) {
	    return;
	}
	/*printf("All threads state%d\n",verify_pending_process());
	int i;
	for(i=0;i<PROCESSES_AVAILABLE;i++){
		printf(" %d, ",process_list[i].status);
	}
		printf(" \n");*/
	if(verify_pending_process()!=1){
       		printf("All threads have been completed\n "); 
		exit(1);
	}
	// TODO: we will handle scheduling threads here.
        address_t pc = (address_t)Round_Robin_Execution;
	deployer(pc);		
	while(process_list[curThread].status!=1){
		deployer(pc);
		select_thread_Round_Robin();
       		//printf("A new thread was added and the current thread is %d\n ",curThread); 		
	}
	select_thread_Round_Robin();
        printf("Random pos %d\n ", curThread); 
   	setalarm_Round_Robin();
	siglongjmp(process_list[curThread].env,1);
}
void my_thread_init_Round_Robin(){

  
	tout_val.it_interval.tv_sec = 0;
	tout_val.it_interval.tv_usec = 0;
	tout_val.it_value.tv_sec = 0; /* set timer for "INTERVAL (10) seconds */
	tout_val.it_value.tv_usec = Quantum;
	setalarm_Round_Robin();
}

void setalarm_Round_Robin(){
    setitimer(ITIMER_REAL, &tout_val,0);
    signal(SIGALRM,alarm_wakeup_Round_Robin); /* set the Alarm signal capture */
}

void alarm_wakeup_Round_Robin ()
{
	Round_Robin_aux();
}



void Round_Robin()
{
 	srand(time(0));
        address_t pc = (address_t)Round_Robin_Execution;
	while(1){
		deployer(pc);
		select_thread_Round_Robin();
		if(process_list[curThread].status==1){		
			my_thread_init_Round_Robin();
			siglongjmp(process_list[curThread].env,1);
		}
	}

}



