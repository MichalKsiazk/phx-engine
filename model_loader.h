

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct model3d m3d_t;
typedef struct model_source model_source_t;


m3d_t* new_m3d(char *source_name);
char* read_model_source(char *source_name);

void read_vertices(m3d_t* model, char* source);
void read_indices(m3d_t* model, char* source);

void free_m3d(m3d_t* model);

float* get_vertices(m3d_t* model);
unsigned int* get_indices(m3d_t* model);
unsigned int get_vertices_size(m3d_t* model);
unsigned int get_indices_size(m3d_t* model);


void print_vertices(m3d_t* model);
void print_indices(m3d_t* model);