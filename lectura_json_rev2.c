#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char **argv){
  FILE *fp;
  char buffer[1024];

  char algo;
  char opera;
  int num_pro;
  int quan;

  PROCESSES_AVAILABLE = malloc(sizeof(int));
  Quantum = malloc(sizeof(int));

  struct json_object *parsed_json;
  struct json_object *algoritmo;
  struct json_object *operacion;
  struct json_object *num_procesos;
  struct json_object *tiempo_llegada;
  struct json_object *cantidad_trabajo;
  struct json_object *quantum;
  struct json_object *tiquetes;

  struct json_object *t_ll; //var temp para guardar cada var del array de tiempo de llegada
  struct json_object *can_tr; //var temp para guardar cada var del array de cantidad_trabajo
  struct json_object *tiq;

  size_t n_tiempo_llegada;//variable para saber el tama;o del arreglo de tiempo de llegada
  size_t n_cantidad_trabajo;//variable para saber el tama;o del arreglo de cantidad de trabajo
  size_t i;//contador para el ciclo for
  size_t j;//contador para imprimir el arreglo

  fp = fopen("lectura.json", "r");
  fread(buffer, 1024, 1, fp);
  fclose(fp);

  parsed_json = json_tokener_parse(buffer);

  json_object_object_get_ex(parsed_json, "algoritmo", &algoritmo);
  algo = json_object_get_string(algoritmo);

  if(algo=="LS"){
    size_t n_tiquetes;

    json_object_object_get_ex(parsed_json, "operacion", &operacion);
    json_object_object_get_ex(parsed_json, "num_procesos", &num_procesos);
    json_object_object_get_ex(parsed_json, "tiempo_llegada", &tiempo_llegada);
    json_object_object_get_ex(parsed_json, "cantidad_trabajo", &cantidad_trabajo);
    json_object_object_get_ex(parsed_json, "quantum_json", &quantum_json);
    json_object_object_get_ex(parsed_json, "tiquetes", &tiquetes);

    n_tiempo_llegada = json_object_array_length(tiempo_llegada);
    n_cantidad_trabajo = json_object_array_length(cantidad_trabajo);
    n_tiquetes = json_object_array_length(tiquetes);

    opera = json_object_get_string(operacion);
    PROCESSES_AVAILABLE = json_object_get_int(num_procesos);
    Quantum = json_object_get_int(quantum);

    Work_by_Process = malloc(PROCESSES_AVAILABLE * sizeof(int));
    Arrival_Time_by_Process = malloc(PROCESSES_AVAILABLE * sizeof(int));
    Tickets_by_Process = malloc(PROCESSES_AVAILABLE * sizeof(int));

    for(i=0;i<PROCESSES_AVAILABLE;i++){
      t_ll = json_object_array_get_idx(tiempo_llegada,i);
      can_tr = json_object_array_get_idx(cantidad_trabajo,i);
      tiq = json_object_array_get_idx(tiquetes,i);
      Tickets_by_Process[i] = json_object_get_int(tiq);
      Arrival_Time_by_Process[i] = json_object_get_int(t_ll);
      Work_by_Process[i] = json_object_get_int(can_tr);
    }


    opera = json_object_get_string(operacion);
    PROCESSES_AVAILABLE = json_object_get_int(num_procesos);
    Quantum = json_object_get_int(quantum);

  }
  else if(algo=="FCFS"){
    json_object_object_get_ex(parsed_json, "num_procesos", &num_procesos);
    json_object_object_get_ex(parsed_json, "tiempo_llegada", &tiempo_llegada);
    json_object_object_get_ex(parsed_json, "cantidad_trabajo", &cantidad_trabajo);

    n_tiempo_llegada = json_object_array_length(tiempo_llegada);
    n_cantidad_trabajo = json_object_array_length(cantidad_trabajo);

    Work_by_Process = malloc(PROCESSES_AVAILABLE * sizeof(int));
    Arrival_Time_by_Process = malloc(PROCESSES_AVAILABLE * sizeof(int));

    for(i=0;i<n_tiempo_llegada;i++){
      t_ll = json_object_array_get_idx(tiempo_llegada,i);
      can_tr = json_object_array_get_idx(cantidad_trabajo,i);
    //tiq = json_object_array_get_idx(tiquetes,i);
    //tiquetes_array[i] = json_object_get_int(tiq);
      Arrival_Time_by_Process[i] = json_object_get_int(t_ll);
      Work_by_Process[i] = json_object_get_int(can_tr);
    }
    opera = json_object_get_string(operacion);
    num_pro = json_object_get_int(num_procesos);

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
