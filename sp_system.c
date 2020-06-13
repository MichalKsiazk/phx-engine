#include "sp_system.h"


void init_sp_system()
{
}

void update_sp_system()
{
	glUseProgram(sp_shader_program);
	//draw_grid(GREEN_COLOR);
	//draw_cube(0,0,0, RED_COLOR);
	//draw_cube(PART_SIZE,0,0, RED_COLOR);
}

void draw_grid(unsigned int color)
{

	glUniform3f(glGetUniformLocation(sp_shader_program, "new_color")
			, GET_COLOR(color, 0)
			, GET_COLOR(color, 1)
			, GET_COLOR(color, 2));

	for(float z = -GRID_SIZE; z < GRID_SIZE; z += PART_SIZE)
	{
		for(float x = -GRID_SIZE; x < GRID_SIZE; x += PART_SIZE)
		{
			draw_line(x,-GRID_SIZE,z,x,GRID_SIZE,z);
		}
	}
}

void draw_cube(float px, float py, float pz, unsigned int color)
{
	glUniform3f(glGetUniformLocation(sp_shader_program, "new_color")
			, GET_COLOR(color, 0)
			, GET_COLOR(color, 1)
			, GET_COLOR(color, 2));
	draw_line(px, py, pz,  px, py + PART_SIZE, pz);
	draw_line(px + PART_SIZE, py, pz,  px + PART_SIZE, py + PART_SIZE, pz);
	draw_line(px, py, pz + PART_SIZE,  px, py + PART_SIZE, pz + PART_SIZE);
	draw_line(px + PART_SIZE, py, pz + PART_SIZE,  px + PART_SIZE, py + PART_SIZE, pz + PART_SIZE);

	draw_line(px, py, pz, px, py, pz + PART_SIZE);
	draw_line(px + PART_SIZE, py, pz + PART_SIZE, px, py, pz + PART_SIZE);
	draw_line(px, py, pz, px + PART_SIZE, py, pz);
	draw_line(px + PART_SIZE, py, pz + PART_SIZE, px + PART_SIZE, py, pz);

	draw_line(px, py + PART_SIZE, pz, px, py + PART_SIZE, pz + PART_SIZE);
	draw_line(px + PART_SIZE, py + PART_SIZE, pz + PART_SIZE, px, py + PART_SIZE, pz + PART_SIZE);
	draw_line(px, py + PART_SIZE, pz, px + PART_SIZE, py + PART_SIZE, pz);
	draw_line(px + PART_SIZE, py + PART_SIZE, pz + PART_SIZE, px + PART_SIZE, py + PART_SIZE, pz);
}
