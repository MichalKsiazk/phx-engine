#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "phx_config.h"
#include "math_utils.h"
#include "renderer.h"

#define GRID_SIZE 5
#define PART_SIZE 1.0f

void init_sp_system();
void update_sp_system();

void draw_grid();
void draw_cube(float px, float py, float pz, unsigned int color);


