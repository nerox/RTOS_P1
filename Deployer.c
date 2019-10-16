#include "Deployer.h"
#include "Controller.h"
void start_clock(){
	time(&start_t);
}
void deployer(address_t func){

	double time_spent;


	/* here, do your time-consuming job */
   	time(&end_t);
	time_spent = difftime(end_t, start_t);
	deploy_verifier(time_spent,func);
}
void deploy_verifier(double time_spent,address_t func){
	int i;
	for (i=0;i<PROCESSES_AVAILABLE;i++){
		if(time_spent>=Arrival_Time_by_Process[i] && process_list[i].status==0){
			printf("Adding a new process to the available list\n");
			process_list[i].status=1;

			setup(i, func);
			availableTreads++;
		}
	}
}
