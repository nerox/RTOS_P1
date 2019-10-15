#include "Lottery.h"

void Lottery_Scheduler_Execution()
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
int select_random_thread(){
	int totalTicketsAvailable=0;
	int randomPos;
	int retpos=0;
	int i;
	for (i=0;i<PROCESSES_AVAILABLE;i++){
		if(process_list[i].status==1){
			totalTicketsAvailable+=Tickets_by_Process[i];
		}
	}
	randomPos=rand() % (totalTicketsAvailable);
	totalTicketsAvailable=0;
	for (i=0;i<PROCESSES_AVAILABLE;i++){
		if(process_list[i].status==1){
			totalTicketsAvailable+=Tickets_by_Process[i];
			if(randomPos/(totalTicketsAvailable)<=0){
				printf("Return pos %d\n ", i); 
				return retpos=i;
			}
		}
	}
	return retpos;
}

void Lottery_Scheduler_aux()
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
       		printf("All threads have been completed %d\n "); 
		exit(1);
	}
	// TODO: we will handle scheduling threads here.
        address_t pc = (address_t)Lottery_Scheduler_Execution;
	deployer(pc);		
	while(process_list[curThread].status!=1){
		deployer(pc);
		curThread= select_random_thread();
       		//printf("All threads available threads have been completed %d\n ",curThread); 		
	}
	curThread= select_random_thread();
        //printf("Random pos %d\n ", curThread); 
   	setalarm();
	siglongjmp(process_list[curThread].env,1);
}
void my_thread_init(){

  
	tout_val.it_interval.tv_sec = 0;
	tout_val.it_interval.tv_usec = 0;
	tout_val.it_value.tv_sec = 0; /* set timer for "INTERVAL (10) seconds */
	tout_val.it_value.tv_usec = Quantum;
	setalarm();
}

void setalarm(){
    setitimer(ITIMER_REAL, &tout_val,0);
    signal(SIGALRM,alarm_wakeup); /* set the Alarm signal capture */
}

void alarm_wakeup ()
{
	Lottery_Scheduler_aux();
}



void Lottery_Scheduler()
{
 	srand(time(0));
        address_t pc = (address_t)Lottery_Scheduler_Execution;
	while(1){
		deployer(pc);
		curThread=select_random_thread();
		if(process_list[curThread].status==1){		
			my_thread_init();
			siglongjmp(process_list[curThread].env,1);
		}
	}

}


