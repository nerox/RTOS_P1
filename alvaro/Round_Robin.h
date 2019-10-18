#ifndef LOTTERY_H
#define LOTTER_H
#include "Scheduler.h"
#include "Controller.h"
#include "Deployer.h"
#include<time.h> 
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>

void my_thread_init_Round_Robin();
void setalarm_Round_Robin();
void alarm_wakeup_Round_Robin();
void Round_Robin_Execution();
void Round_Robin_aux();
void selectThread(int position);
void select_thread_Round_Robin();
void Round_Robin_Scheduler();
void Round_Robin();
#endif
