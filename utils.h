
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdint.h>

#include "bmfont.h"


static uint64_t fps;
static double last_time;
static int c_fps;

void init_counter();
void count_fps();