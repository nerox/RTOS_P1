#include "Round_Robin.h"
#include "interfaz.h"
void timer_handler_RR (int signum);
void alarma_RR();

void Round_Robin_Execution()
{
    unsigned int n = work_unit_size*Work_by_Process[curThread];
    double ans=0.0;
    for (uint i = 0; i <= n; i++) {
	ans+=(4*pow(-1,i))/(2*i+1);
	calculated_pi_process[curThread]= ans;
	progress_by_process[curThread]= 100*((double)i/(double)n);
    }
	process_list[curThread].status=2;
	Round_Robin_aux();
	while (1) {

	}
	
}

void select_thread_Round_Robin(){
	selectThread(curThread+1);
}
void selectThread(int position){
	int i=position;
	int count;
	//printf("All threads state%d\n",curThread);
	for (count=0;count<PROCESSES_AVAILABLE;count++){
		if(i==PROCESSES_AVAILABLE){
			i=0;
		}
		if (process_list[i].status==1){
			curThread=i;
			break;
		}
		else{
			i++;
		}
	}
}
void Round_Robin_aux()
{
	if(process_list[curThread].status!=2){
		process_list[curThread].status=1;
	}
	int ret_val = sigsetjmp(process_list[curThread].env,1);
	if (ret_val == 1) {
	    return;
	}
	//printf("All threads state%d\n",verify_pending_process());
	/*int i;
	for(i=0;i<PROCESSES_AVAILABLE;i++){
		printf(" %d, ",process_list[i].status);
	}
		printf(" \n");*/
	if(verify_pending_process()!=1){
       		printf("All threads have been completed\n "); 
		usleep(1000000);
	}
	// TODO: we will handle scheduling threads here.
        address_t pc = (address_t)Round_Robin_Execution;
	deployer(pc);		
	/*while(process_list[curThread].status!=1){
		deployer(pc);
		select_thread_Round_Robin();
       		//printf("A new thread was added and the current thread is %d\n ",curThread); 		
	}*/
	select_thread_Round_Robin();
        //printf("Random pos %d\n ", curThread); 
   	//setalarm_Round_Robin();
	if(process_list[curThread].status!=2){
		process_list[curThread].status=3;
	}
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
			//my_thread_init_Round_Robin();
			alarma_RR();
			siglongjmp(process_list[curThread].env,1);
		}
	}

}

void timer_handler_RR (int signum)
{
 static int count = 0;
 printf ("timer expired %d times\n", ++count);
}
void alarma_RR(){
 struct sigaction sa;
 struct itimerval timer;

 /* Install timer_handler as the signal handler for SIGVTALRM. */
 memset (&sa, 0, sizeof (sa));
 sa.sa_handler = &Round_Robin_aux;
 sigaction (SIGVTALRM, &sa, NULL);

 if(Quantum<999999){
 /* Configure the timer to expire after 250 msec... */
 timer.it_value.tv_sec = 0;
 timer.it_value.tv_usec = Quantum;
 /* ... and every 250 msec after that. */
 timer.it_interval.tv_sec = 0;
 timer.it_interval.tv_usec = Quantum;
 /* Start a virtual timer. It counts down whenever this process is
   executing. */
}
else{
 /* Configure the timer to expire after 250 msec... */
 timer.it_value.tv_sec = Quantum/1000000;
 timer.it_value.tv_usec = 0;
 /* ... and every 250 msec after that. */
 timer.it_interval.tv_sec = Quantum/1000000;
 timer.it_interval.tv_usec = 0;
 /* Start a virtual timer. It counts down whenever this process is
   executing. */
}
 setitimer (ITIMER_VIRTUAL, &timer, NULL);
}




