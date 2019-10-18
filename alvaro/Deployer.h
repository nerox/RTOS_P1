#ifndef DEPLOYER_H
#define DEPLOYER_H
#include "Scheduler.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

time_t start_t, end_t;
int Alarm_Signaling ();
void timer_handler (int signum);
void deployer(address_t func);
void deploy_verifier(double time_spent,address_t func);
void start_clock();
#endif

