#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include "atom.h"

#include "atom.h"
#include "camera.h"
#include "phx_config.h"
#include "shader.h"
#include "model_loader.h"

#include <cglm/cglm.h>


unsigned int common_vbo;
unsigned int common_vao;
unsigned int common_ibo;
unsigned int common_vao_lenght;

unsigned int floor_vbo;
unsigned int floor_vao;
unsigned int floor_ibo;
unsigned int floor_vao_lenght;

GLuint atom_vert_shader; 
GLuint atom_geom_shader;
GLuint atom_frag_shader;

GLuint atom_shader_program;

int gen_vbo(float *vertices, unsigned int vertices_size);
void render_shape(unsigned int vao_id, unsigned int vao_size);

void init_renderer();

void render_atoms(atom3d** atoms, unsigned int atoms_count, float scale);
void move_camera(GLFWwindow* window);

void gen_model(m3d_t* model, unsigned int* vbo, unsigned int* vao, unsigned int* ibo, unsigned int* lenght);

void render_scenery();

