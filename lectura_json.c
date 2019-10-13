#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char **argv){
  FILE *fp;
  char buffer[1024];

  char algo;
  char opera;
  int num_pro;

  struct json_object *parsed_json;
  struct json_object *algoritmo;
  struct json_object *operacion;
  struct json_object *num_procesos;
  struct json_object *tiempo_llegada;
  struct json_object *cantidad_trabajo;

  struct json_object *t_ll; //var temp para guardar cada var del array de tiempo de llegada
  struct json_object *can_tr; //var temp para guardar cada var del array de cantidad_trabajo

  size_t n_tiempo_llegada;//variable para saber el tama;o del arreglo de tiempo de llegada
  size_t n_cantidad_trabajo;//variable para saber el tama;o del arreglo de cantidad de trabajo
  size_t i;//contador para el ciclo for
  size_t j;//contador para imprimir el arreglo

  fp = fopen("lectura.json", "r");
  fread(buffer, 1024, 1, fp);
  fclose(fp);

  parsed_json = json_tokener_parse(buffer);

  json_object_object_get_ex(parsed_json, "algoritmo", &algoritmo);
  json_object_object_get_ex(parsed_json, "operacion", &operacion);
  json_object_object_get_ex(parsed_json, "num_procesos", &num_procesos);
  json_object_object_get_ex(parsed_json, "tiempo_llegada", &tiempo_llegada);
  json_object_object_get_ex(parsed_json, "cantidad_trabajo", &cantidad_trabajo);

  n_tiempo_llegada = json_object_array_length(tiempo_llegada);
  n_cantidad_trabajo = json_object_array_length(cantidad_trabajo);

  int tiempo_array[json_object_get_int(num_procesos)];
  int trabajo_array[json_object_get_int(num_procesos)];

  for(i=0;i<n_tiempo_llegada;i++){
    t_ll = json_object_array_get_idx(tiempo_llegada,i);
    can_tr = json_object_array_get_idx(cantidad_trabajo,i);
    tiempo_array[i] = json_object_get_int(t_ll);
    trabajo_array[i] = json_object_get_int(can_tr);
  }

  algo = json_object_get_string(algoritmo);
  opera = json_object_get_string(operacion);
  num_pro = json_object_get_int(num_procesos);

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
