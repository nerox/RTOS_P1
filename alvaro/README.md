# RTOS_P1
Proyecto 1 RTOS

Como compilar :
gcc Scheduler_Controller.c Quick_Sort.c Deployer.c Scheduler.c Lottery.c lectura_json.c  Round_Robin.c project1_scheduling_rtos.c interfaz.c -lm -ljson-c -fPIC `pkg-config --libs --cflags gtk+-3.0` -o RTOS
