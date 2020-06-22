#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <math.h>

#include "phx_config.h"
#include "math_utils.h"
#include "renderer.h"

#define GRID_SIZE 20
#define PART_SIZE 1.0f

typedef struct sp_unit sp_unit;
typedef struct sp_cell sp_cell;

static sp_cell* sp_grid [GRID_SIZE][GRID_SIZE][GRID_SIZE];

void init_sp_system();
void update_sp_system();
void reset_sp_system();

void draw_grid();
void draw_cube(float px, float py, float pz, unsigned int color);

sp_cell* create_sp_cell(int x, int y, int z);
void clear_sp_cell(sp_cell* cell);
void subscribe_to_sp_cell(double x, double y, double z);
sp_cell* get_cell(double x, double y, double z);



