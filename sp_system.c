#include "sp_system.h"



typedef struct sp_unit
{
	unsigned int id;
	sp_unit* next; 
}sp_unit;


typedef struct sp_cell
{
	vec3d* pos;
	unsigned long long id;
	unsigned int index;
	unsigned int present_atoms_count;
	sp_unit* present_atoms;
}sp_cell;

void init_sp_system()
{
	int max = GRID_SIZE;
	for(int x = 0; x < max; x++)
	{
		for(int y = 0; y < max; y++)
		{
			for(int z = 0; z < max; z++)
			{
				sp_grid[x][y][z] = create_sp_cell(x, y, z); 
			}
		}
	}
}

void update_sp_system()
{
	glUseProgram(sp_shader_program);
	draw_grid(DEFAULT_ATOM_COLOR);
}

void reset_sp_system()
{
	int max = GRID_SIZE;
	for(int x = 0; x < max; x++)
	{
		for(int y = 0; y < max; y++)
		{
			for(int z = 0; z < max; z++)
			{
				clear_sp_cell(sp_grid[x][y][z]);
			}
		}
	}
}

void draw_grid(unsigned int color)
{
	int max = GRID_SIZE;
	for(int x = 0; x < max; x++)
	{
		for(int y = 0; y < max; y++)
		{
			for(int z = 0; z < max; z++)
			{
				if(sp_grid[x][y][z]->present_atoms_count > 0)
				{
					sp_cell* pos = sp_grid[x][y][z]->pos;
					float rel_x = (float) get_v3d_x(pos);
					float rel_y = (float) get_v3d_y(pos);
					float rel_z = (float) get_v3d_z(pos);
					draw_cube(rel_x, rel_y, rel_z, color);
				}
			}
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

sp_cell* create_sp_cell(int x, int y, int z)
{
	double rel = ((double)GRID_SIZE) / 2.0;
	sp_cell* new_cell = (sp_cell*) malloc(sizeof(sp_cell));
	new_cell->pos = new_vec3d(((double)x) - rel, ((double)y) - rel, ((double)z) - rel);
	new_cell->present_atoms_count = 0;
	new_cell->present_atoms = NULL;
	return new_cell;
}

void clear_sp_cell(sp_cell* cell)
{
	if(cell->present_atoms_count == 0)
	{
		return;
	}
	cell->present_atoms_count = 0;

	sp_unit* current = cell->present_atoms;
	while(current != NULL)
	{
		sp_unit* next = cell->present_atoms->next;
		free(current);
		current = next;
	}

}

void subscribe_to_sp_cell(double x, double y, double z)
{
	sp_cell* cell = get_cell(x, y, z);
	cell->present_atoms_count++;
	sp_unit* current = cell->present_atoms;
	if(current != NULL)
	{
		while (current->next != NULL)
		{
			current = current->next;
		}
	}
	
	current = (sp_unit*) malloc(sizeof(sp_unit));
	//current->next->id = id;
	current->next = NULL;
}

sp_cell* get_cell(double x, double y, double z)
{
	int rel = GRID_SIZE / 2;
	int rx = (int)floor(x) + rel;
	int ry = (int)floor(y) + rel;
	int rz = (int)floor(z) + rel;
	return sp_grid[rx][ry][rz];
}










