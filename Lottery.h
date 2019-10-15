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

void my_thread_init();
void setalarm();
void alarm_wakeup ();
void Lottery_Scheduler_Execution();
void Lottery_Scheduler_aux();
void Lottery_Scheduler();
#endif
