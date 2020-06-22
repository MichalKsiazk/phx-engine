#include "math_utils.h"

#include <stdio.h>
#include <stdlib.h> 

typedef struct atom3d atom3d;
typedef struct collision cls_t;
typedef struct atomic_bond atomic_bond;


struct atom3d_props;

cls_t* new_cls_t(int id, cls_t* next);
void push_cls(atom3d* atom, cls_t* cls);

uint8_t check_for_cls(atom3d* atom, int cls_id);
void reset_cls_list(atom3d* atom);

atom3d* init_atom3d(unsigned int id, vec3d* pos, double mass, double radius, vec3d* translation);
atomic_bond* init_atomic_bond(int index_a, int index_b, double damping, double k);

void move_atom3d(atom3d* atom);
void geometry_render_atom3d(struct atom3d* ptr, int shader_program_id);
void instance_render_atom3d(struct atom3d* ptr, int shader_program_id, unsigned int vao_lenght);

vec3d* get_atom_pos(atom3d* atom);
vec3d* get_translation(atom3d* atom);

void translate_atom(atom3d* atom);
size_t get_atom3d_size();

void set_outer_border_color(atom3d* atom, float r, float g, float b);

void set_color(atom3d* atom, unsigned int color);

double get_radius(atom3d* atom);
double get_mass(atom3d* atom);


