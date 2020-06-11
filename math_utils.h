#include <math.h>


#define M_PI 3.14159265358979323846

#define TO_RADIANS(degrees)((M_PI * degrees)/180)

typedef struct vec3d vec3d;
typedef struct vec3f vec3f;


vec3d* new_vec3d(double x, double y, double z);
vec3f* new_vec3f(float x, float y, float z);

vec3d* copy_vec3d(vec3d*);

double get_v3d_x(vec3d*);
double get_v3d_y(vec3d*);
double get_v3d_z(vec3d*);

float get_v3f_x(vec3f*);
float get_v3f_y(vec3f*);
float get_v3f_z(vec3f*);


double distance2d(vec3d* a, vec3d* b);
double distance3d(vec3d* a, vec3d* b);

void move_vec3d(vec3d* vec, double x, double y, double z);
void move_vec3d_t(vec3d* vec, vec3d* t_vec);
void divide_vec3d(vec3d* vec, double x, double y, double z);
void move_towards(vec3d* vec, vec3d* original, vec3d* target, double move_dst);
void set_vec3d(vec3d* vec, double x, double y, double z);

void invert_vec3d(vec3d*);

vec3d* get_dir_normalized(vec3d* origin, vec3d* target);

void move_in_direction(vec3d* vec, vec3d* dir, double dst);

vec3d* zero_point;


void set_vec3f(vec3f* vec, float x, float y, float z);

double random_range(double min, double max);
void set_random_seed();

float deg_to_rad(float deg);