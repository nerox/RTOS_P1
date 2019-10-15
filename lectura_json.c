#include "Lectura_json.h"
#include "Controller.h"

void parse_Data_From_File(){


	fp = fopen("lectura.json", "r");
	fread(buffer, 1024, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "algoritmo", &algoritmo);
	json_object_object_get_ex(parsed_json, "operacion", &operacion);
	json_object_object_get_ex(parsed_json, "num_procesos", &num_procesos);
	json_object_object_get_ex(parsed_json, "quantum", &quantum_json);
	json_object_object_get_ex(parsed_json, "tiempo_llegada", &tiempo_llegada);
	json_object_object_get_ex(parsed_json, "cantidad_trabajo", &cantidad_trabajo);
	json_object_object_get_ex(parsed_json, "tiquetes", &tiquetes);
	n_tiempo_llegada = json_object_array_length(tiempo_llegada);
	n_cantidad_trabajo = json_object_array_length(cantidad_trabajo);
	PROCESSES_AVAILABLE=malloc(sizeof(int));
	Quantum=malloc(sizeof(int));
	PROCESSES_AVAILABLE=json_object_get_int(num_procesos);
	Quantum=json_object_get_int(quantum_json);

	Work_by_Process=  malloc(PROCESSES_AVAILABLE * sizeof(int));
	Arrival_Time_by_Process=  malloc(PROCESSES_AVAILABLE * sizeof(int));
	Tickets_by_Process=  malloc(PROCESSES_AVAILABLE * sizeof(int));
	for(i=0;i<PROCESSES_AVAILABLE;i++){
	t_ll = json_object_array_get_idx(tiempo_llegada,i);
	can_tr = json_object_array_get_idx(cantidad_trabajo,i);
	tiquets_temp = json_object_array_get_idx(tiquetes,i);

	Arrival_Time_by_Process[i] = json_object_get_int(t_ll);
	Work_by_Process[i] = json_object_get_int(can_tr);
	Tickets_by_Process[i]  = json_object_get_int(tiquets_temp);
	}

	algo = json_object_get_string(algoritmo);
	opera = json_object_get_string(operacion);

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
