#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "Controller.h"
#include <setjmp.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

typedef unsigned long address_t;
#define JB_SP 6
#define JB_PC 7


#define SECOND 1000000
struct itimerval tout_val;
// This is the Thread Control Block. We can use the same structure for our htreading,
// but with 1000 instead of 2.

void setup(int num,address_t pc);
address_t translate_address(address_t addr);
#endif

