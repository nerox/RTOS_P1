#Compila Programa fuente

CC = gcc
#CFLAGS1 = -pg -fopenmp
CFLAGS1 = -o
CFLAGS2 = `pkg-config --libs --cflags gtk+-3.0` 
Archivo = project1_scheduling_rtos
PATHBIN = ../
Format = .c
INCS1 = 
INCS2 = 
INCS3 = -I../include/
LIBS =  -lm
PATHLIB = -L../lib/
CFLAGS_LIB = -Bdynamic
MY_LIB = libkernel_img.so

All: binario

binario: $(Archivo).c 
	$(CC) $(CFLAGS1) $(PATHBIN)$(Archivo) $(Archivo)$(Format) $(INCS1) $(INCS2) $(INCS3) $(LIBS) $(PATHLIB) $(CFLAGS_LIB) $(PATHLIB)$(MY_LIB)



