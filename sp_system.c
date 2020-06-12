#include "sp_system.h"


void init_sp_system()
{
}

void update_sp_system()
{
	draw_grid();
}

void draw_grid()
{
	glUseProgram(sp_shader_program);

	for(float z = -GRID_SIZE; z < GRID_SIZE; z += PART_SIZE)
	{
		for(float x = -GRID_SIZE; x < GRID_SIZE; x += PART_SIZE)
		{
			draw_line(x,-GRID_SIZE,z,x,GRID_SIZE,z);
		}
	}


}
