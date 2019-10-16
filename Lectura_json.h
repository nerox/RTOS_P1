#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <json-c/json.h>
#include <string.h>
FILE *fp;
char buffer[1024];

char *algo;
char opera;

struct json_object *parsed_json;
struct json_object *algoritmo;
struct json_object *operacion;
struct json_object *num_procesos;
struct json_object *quantum_json;
struct json_object *tiempo_llegada;
struct json_object *cantidad_trabajo;
struct json_object *tiquetes;
struct json_object *tiq;
struct json_object *t_ll; //var temp para guardar cada var del array de tiempo de llegada
struct json_object *can_tr; //var temp para guardar cada var del array de cantidad_trabajo
struct json_object *tiquets_temp; //var temp para guardar cada var del array de tiquetes
size_t n_tiempo_llegada;//variable para saber el tama;o del arreglo de tiempo de llegada
size_t n_cantidad_trabajo;//variable para saber el tama;o del arreglo de cantidad de trabajo
size_t i;//contador para el ciclo for
size_t j;//contador para imprimir el arreglo
void parse_Data_From_File();
#endif
