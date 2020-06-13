#include "math_utils.h"

#define WINDOW_SIZE_X   1800
#define WINDOW_SIZE_Y   1000


#define WINDOW_TITLE "phx engine"


#define GLOBAL_ATOM_RADIUS 0.05
#define GLOBAL_ATOM_RESOLUTION 12

#define GRAVITATE_AT_ZERO 0

//GEOMETRY_RENDERER
//INSTANCE_RENDERER

#define INSTANCE_RENDERER


#define PHX_ASPECT_RATIO ((double)WINDOW_SIZE_Y / (double)WINDOW_SIZE_X)



#define GET_COLOR(a, b) color_table[a * 3 + b]

//COLORS
#define DEFAULT_ATOM_COLOR 	0
#define RED_COLOR			1
#define GREEN_COLOR			2
#define BLUE_COLOR 			3

extern float color_table[];
unsigned int color_changes;
unsigned int detected_collisions;
