#include "Controller.h"
#include "Lectura_json.h"
void parse_Data_From_File(){
	FILE *fp;
	char buffer[1024];

	int num_pro;
	int quan;

	PROCESSES_AVAILABLE = malloc(sizeof(int));
	Quantum = malloc(sizeof(int));

	fp = fopen("lectura.json", "r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "algoritmo", &algoritmo);
	json_object_object_get_ex(parsed_json, "operacion", &operacion);
	json_object_object_get_ex(parsed_json, "num_procesos", &num_procesos);
	json_object_object_get_ex(parsed_json, "tiempo_llegada", &tiempo_llegada);
	json_object_object_get_ex(parsed_json, "cantidad_trabajo", &cantidad_trabajo);
	PROCESSES_AVAILABLE = json_object_get_int(num_procesos);
	algo = json_object_get_string(algoritmo);
	n_tiempo_llegada = json_object_array_length(tiempo_llegada);
	n_cantidad_trabajo = json_object_array_length(cantidad_trabajo);
	Work_by_Process = malloc(PROCESSES_AVAILABLE * sizeof(int));
	Arrival_Time_by_Process = malloc(PROCESSES_AVAILABLE * sizeof(int));

	opera = json_object_get_string(operacion);
	if(PROCESSES_AVAILABLE >= 5 && PROCESSES_AVAILABLE <=50){
		if(strcmp(algo, "LS")==0){
			algorithm=0;
			size_t n_tiquetes;
			json_object_object_get_ex(parsed_json, "quantum", &quantum_json);
			json_object_object_get_ex(parsed_json, "tiquetes", &tiquetes);
			n_tiquetes = json_object_array_length(tiquetes);
			Quantum = json_object_get_int(quantum_json);
			Tickets_by_Process = malloc(PROCESSES_AVAILABLE * sizeof(int));

			for(i=0;i<PROCESSES_AVAILABLE;i++){
				t_ll = json_object_array_get_idx(tiempo_llegada,i);
				can_tr = json_object_array_get_idx(cantidad_trabajo,i);
				tiq = json_object_array_get_idx(tiquetes,i);
				Tickets_by_Process[i] = json_object_get_int(tiq);
				Arrival_Time_by_Process[i] = json_object_get_int(t_ll);
				Work_by_Process[i] = json_object_get_int(can_tr);
			}


		}
		else if(strcmp(algo, "FCFS")==0){
			algorithm=1;
			for(i=0;i<PROCESSES_AVAILABLE;i++){
				t_ll = json_object_array_get_idx(tiempo_llegada,i);
				can_tr = json_object_array_get_idx(cantidad_trabajo,i);
				//tiq = json_object_array_get_idx(tiquetes,i);
				//tiquetes_array[i] = json_object_get_int(tiq);
				Arrival_Time_by_Process[i] = json_object_get_int(t_ll);
				Work_by_Process[i] = json_object_get_int(can_tr);
			}

		}
		else if (strcmp(algo, "RR")==0){

			algorithm=2;
			json_object_object_get_ex(parsed_json, "quantum", &quantum_json);
			Quantum = json_object_get_int(quantum_json);

			for(i=0;i<PROCESSES_AVAILABLE;i++){
				t_ll = json_object_array_get_idx(tiempo_llegada,i);
				can_tr = json_object_array_get_idx(cantidad_trabajo,i);
				Arrival_Time_by_Process[i] = json_object_get_int(t_ll);
				Work_by_Process[i] = json_object_get_int(can_tr);
			}
		}
	}
	else{
		printf("%s\n","Cantidad de procesos ingresados es incorrecta favor de ingresar un valor entre 5 o 50 inclusive" );
		exit(1);
	}
  //"quantum": "1111",
  //"tiquetes":["5","25","20","15","10"]
  //printf("Algoritmo a utilizar: %s\n", json_object_get_string(algoritmo));
  //printf("Operacion: %s\n", json_object_get_string(operacion));
  //printf("Numero de Procesos: %d\n", json_object_get_int(num_procesos));

  //for(j=0;j<json_object_get_int(num_procesos);j++){
    //printf("Element[%d] = %d\n",j,tiempo_array[j] );
  //}
  //for(j=0;j<json_object_get_int(num_procesos);j++){
    //printf("Element[%d] = %d\n",j,trabajo_array[j] );
  //}
}
