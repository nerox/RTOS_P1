#MAKEFILE QUE CREARÁ LA BIBLIOTECA DINÁMICA

FLAGS= -fPIC `pkg-config --libs --cflags gtk+-3.0`
SRC= interfaz

All: $(SRC).so $(SRC).o
$(SRC).so: $(SRC).o
	ld -o lib$(SRC).so $(SRC).o -shared


$(SRC).o: $(SRC).c 
	gcc -c $(SRC).c $(FLAGS) 










