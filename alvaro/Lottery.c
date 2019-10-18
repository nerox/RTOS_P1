#include "Lottery.h"
#include "interfaz.h"
void timer_handler (int signum);
void alarma();

void Lottery_Scheduler_Execution()
{

    // double ans = 4;
    // float percentage;
    unsigned int n = work_unit_size*Work_by_Process[curThread];
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
	Lottery_Scheduler_aux();
	while (1) {

	}

	
}
int select_random_thread(){
	int totalTicketsAvailable=0;
	int randomPos;
	int retpos=curThread;
	int i;
    	update_progress_var.status = "Waiting";//g_string_new (test);
	for (i=0;i<PROCESSES_AVAILABLE;i++){
		if(process_list[i].status==1){
			totalTicketsAvailable+=Tickets_by_Process[i];
		}
	}
	randomPos=rand() % (totalTicketsAvailable+1);
	totalTicketsAvailable=0;
	for (i=0;i<PROCESSES_AVAILABLE;i++){
		if(process_list[i].status==1){
			totalTicketsAvailable+=Tickets_by_Process[i];
			if(randomPos<=totalTicketsAvailable){
				//printf("Return pos %d\n ", i); 
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
       		printf("All threads have been completed\n "); 
		exit(1);
	}
	// TODO: we will handle scheduling threads here.
        address_t pc = (address_t)Lottery_Scheduler_Execution;
	deployer(pc);		
	/*while(process_list[curThread].status!=1){
		deployer(pc);
		curThread= select_random_thread();
       		printf("A new thread was added and the current thread is %d\n ",curThread); 		
	}*/
	curThread= select_random_thread();
        //printf("Random pos %d\n ", curThread); 
   	//setalarm();
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
			//my_thread_init();
			alarma();
			siglongjmp(process_list[curThread].env,1);
		}

	}

}

void timer_handler (int signum)
{
 static int count = 0;
 printf ("timer expired %d times\n", ++count);
}
void alarma(){
 struct sigaction sa;
 struct itimerval timer;

 /* Install timer_handler as the signal handler for SIGVTALRM. */
 memset (&sa, 0, sizeof (sa));
 sa.sa_handler = &Lottery_Scheduler_aux;
 sigaction (SIGVTALRM, &sa, NULL);

 /* Configure the timer to expire after 250 msec... */
 timer.it_value.tv_sec = 0;
 timer.it_value.tv_usec = Quantum;
 /* ... and every 250 msec after that. */
 timer.it_interval.tv_sec = 0;
 timer.it_interval.tv_usec = Quantum;
 /* Start a virtual timer. It counts down whenever this process is
   executing. */
 setitimer (ITIMER_VIRTUAL, &timer, NULL);
}


