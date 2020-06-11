#include <math.h>

#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 

#include "math_utils.h"
#include "phx_config.h"


typedef struct vec3d
{
    double x;
    double y;
    double z;
} vec3d;

typedef struct vec3f
{
    float x;
    float y;
    float z;
} vec3f;

vec3d* new_vec3d(double x, double y, double z)
{
    vec3d* retval = malloc(sizeof(vec3d));
    retval->x = x;
    retval->y = y;
    retval->z = z;
    return retval;
}

vec3f* new_vec3f(float x, float y, float z)
{
    vec3f* retval = malloc(sizeof(vec3f));
    retval->x = x;
    retval->y = y;
    retval->z = z;
    return retval;
}

vec3d* copy_vec3d(vec3d* vec)
{
    vec3d* retvec = new_vec3d(vec->x, vec->y, vec->z);
    return retvec;
}

double get_v3d_x(vec3d* vec)
{
    return vec->x;
}
double get_v3d_y(vec3d* vec)
{
    return vec->y;
}
double get_v3d_z(vec3d* vec)
{
    return vec->z;
}


float get_v3f_x(vec3f* vec)
{
    return vec->x;
}
float get_v3f_y(vec3f* vec)
{
    return vec->y;
}
float get_v3f_z(vec3f* vec)
{
    return vec->z;
}



double distance2d(vec3d* a, vec3d* b)
{
    return sqrt(pow(1 / PHX_ASPECT_RATIO * (a->x - b->x), 2) + pow(a->y - b->y, 2));
}

double distance3d(vec3d* a, vec3d* b)
{
    return sqrt(pow(1 / PHX_ASPECT_RATIO * (a->x - b->x), 2) + pow(a->y - b->y, 2) + pow(a->z - b->z, 2));
}

void move_vec3d(vec3d* vec, double x, double y, double z)
{
    vec->x += x;
    vec->y += y;
    vec->z += z;
}

void divide_vec3d(vec3d* vec, double x, double y, double z)
{
    vec->x /= x;
    vec->y /= y;
    vec->z /= z;
}

void move_vec3d_t(vec3d* vec, vec3d* t_vec)
{
    vec->x += t_vec->x;
    vec->y += t_vec->y;
    vec->z += t_vec->z;
}

void move_towards(vec3d* vec, vec3d* original, vec3d* target, double move_dst)
{
    double dst = distance3d(original, target);
    double dst_x = (original->x - target->x) / dst;
    double dst_y = (original->y - target->y) / dst;
    double dst_z = (original->z - target->z) / dst;
    move_vec3d(vec, -move_dst * dst_x, -move_dst * dst_y, -move_dst * dst_z);
}

void set_vec3d(vec3d* vec, double x, double y, double z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

void invert_vec3d(vec3d* vec)
{
    vec->x = -vec->x;
    vec->y = -vec->y;
    vec->z = -vec->z;
}

void set_vec3f(vec3f* vec, float x, float y, float z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

vec3d* get_dir_normalized(vec3d* origin, vec3d* target)
{
    double dst = distance3d(origin, target);
    double x = (origin->x - target->x) / dst;
    double y = (origin->y - target->y) / dst;
    double z = (origin->z - target->z) / dst;
    return new_vec3d(x,y,z);
}

void move_in_direction(vec3d* vec, vec3d* dir, double dst)
{
    move_vec3d(vec, -dst * dir->x, -dst * dir->y, -dst * dir->z);
}

double random_range(double min, double max)
{


    int random_min = (int)(min * 100);
    int random_max = (int)(max * 100);

    int rnd = (rand() % (random_min - random_max + 1)) + random_min; 

    return ((float)rnd) / 100.0f;
}

void set_random_seed()
{
    time_t t;
    srand((unsigned) time(&t));
}

float deg_to_rad(float deg)
{
    return (M_PI * deg) / 180;
}
