#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h> 

#include <cglm/cglm.h>

#include "atom.h"
#include "math_utils.h"
#include "phx_config.h"

#define TO_RADIANS(degrees)((M_PI * degrees)/180)

typedef struct atom3d
{
    unsigned int id;
    vec3d* position;
    vec3d* translation;
    double velocity;
    vec3f* outer_border_color;
    cls_t* collisions;
    unsigned int color;
}atom3d;

typedef struct collision
{
    int index;
    struct collision* next;
} cls_t;

struct atom3d_props
{
};


struct atom3d* init_atom3d(unsigned int id, vec3d* position, vec3d* translation)
{
    atom3d* atom = (atom3d*)malloc(sizeof(atom3d));
    atom->id = id;
    atom->position = position;
    atom->outer_border_color = new_vec3f(0.0f,1.0f,0.0f);
	atom->color = 0;
    if(translation == NULL)
    {
        atom->translation = new_vec3d(0,0,0);
    }
    else
    {
        atom->translation = translation;
    }
    atom->collisions = new_cls_t(-1, NULL);
    return atom;
    
}

cls_t* new_cls_t(int id, cls_t* next)
{
    cls_t* new_cls = (cls_t*) malloc(sizeof(cls_t));
    new_cls->index = id;
    new_cls->next = next;
    return new_cls;
}

void push_cls(atom3d* atom, cls_t* cls)
{

    cls_t* current = atom->collisions;


    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = cls;

    
}

uint8_t check_for_cls(atom3d* atom, int cls_id)
{
    cls_t* current = atom->collisions;

    while (current->next != NULL)
    {
        current = current->next;
        if(current->index == cls_id)
        {
            return 0x1;
        }

    }
    return 0x0;
}

void reset_cls_list(atom3d* atom)
{
    cls_t* current = atom->collisions;

     while (1)
     {
        cls_t* next;
        if(current->next != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
        else { break; }
     }
     atom->collisions = new_cls_t(-1, NULL);
}

size_t get_atom3d_size()
{
    return sizeof(atom3d);
}

void geometry_render_atom3d(struct atom3d* ptr, int shader_program_id)
{

    
    vec3f* outer_color = ptr->outer_border_color;


    glUniform3f(glGetUniformLocation(shader_program_id, "border_color")
    , (float)get_v3f_x(outer_color)
    , (float)get_v3f_y(outer_color)
    , (float)get_v3f_z(outer_color));



    //GLint position_location = glGetUniformLocation(shader_program_id, "position");

    vec3d* pos = ptr->position;




    mat4 transformation;
    glm_mat4_identity(transformation);
    glm_translate(transformation, (vec3){(float)get_v3d_x(pos), (float)get_v3d_y(pos), (float)get_v3d_z(pos)});
    glm_rotate(transformation, TO_RADIANS(0), (vec3){1,0,0});
    glm_rotate(transformation, TO_RADIANS(0), (vec3){0,1,0});
    glm_rotate(transformation, TO_RADIANS(0), (vec3){0,0,1});
    glm_scale(transformation, (vec3){1,1,1});

    glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "transformation"), 1, GL_FALSE, (float*)transformation);


    glDrawArrays(GL_POINTS, 0, 3);
}

void instance_render_atom3d(struct atom3d* ptr, int shader_program_id, unsigned int vao_lenght)
{
    vec3f* outer_color = ptr->outer_border_color;
	static unsigned int current_color;

    //GLint position_location = glGetUniformLocation(shader_program_id, "position");

    vec3d* pos = ptr->position;

    mat4 transformation;
    glm_mat4_identity(transformation);
    glm_translate(transformation, (vec3){(float)get_v3d_x(pos), (float)get_v3d_y(pos), (float)get_v3d_z(pos)});
    glm_rotate(transformation, TO_RADIANS(0), (vec3){1,0,0});
    glm_rotate(transformation, TO_RADIANS(0), (vec3){0,1,0});
    glm_rotate(transformation, TO_RADIANS(0), (vec3){0,0,1});
    glm_scale(transformation, (vec3){1,1,1});

    glUniformMatrix4fv(glGetUniformLocation(shader_program_id, "transformation"), 1, GL_FALSE, (float*)transformation);
	if(ptr->color != current_color)
	{
		glUniform3f(glGetUniformLocation(shader_program_id, "new_color"),
				GET_COLOR(ptr->color, 0),
				GET_COLOR(ptr->color, 1),
				GET_COLOR(ptr->color, 2));
		current_color = ptr->color;
		color_changes++;
	}
    glDrawElements(GL_TRIANGLES, vao_lenght, GL_UNSIGNED_INT, NULL);
}



void move_atom3d(atom3d* atom)
{
    move_vec3d_t(atom->position, atom->translation);
}

vec3d* get_atom_pos(atom3d* atom)
{
    return atom->position;
}
vec3d* get_translation(atom3d* atom)
{
    return atom->translation;
}

void set_outer_border_color(atom3d* atom, float r, float g, float b)
{
    set_vec3f(atom->outer_border_color, r, g, b);
}

void set_color(atom3d* atom, unsigned int color)
{
	atom->color = color;
}
