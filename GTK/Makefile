#Compila Programa fuente

CC = gcc
#CFLAGS1 = -pg -fopenmp
CFLAGS1 = -o
CFLAGS2 = `pkg-config --libs --cflags gtk+-3.0`
#Archivo = example4
Archivo = project1_scheduling_rtos_thread
Format = .c
PATHBIN =
INCS1 =
INCS2 =
INCS3 =
LIBS = -lm
PATHLIB =
MY_LIB =

All: binario

binario: $(Archivo).c
	$(CC) $(CFLAGS1) $(PATHBIN)$(Archivo) $(Archivo)$(Format) $(CFLAGS2) $(INCS1) $(INCS2) $(INCS3) $(LIBS) $(PATHLIB)  $(PATHLIB)$(MY_LIB)
