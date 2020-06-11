#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>


#define GEN_VS(fn) gen_shader(GL_VERTEX_SHADER, fn)
#define GEN_GS(fn) gen_shader(GL_GEOMETRY_SHADER, fn)
#define GEN_FS(fn) gen_shader(GL_FRAGMENT_SHADER, fn)

GLuint gen_shader_program(GLuint vs, GLuint gs, GLuint fs);
GLuint gen_shader(GLenum shader_type, char *shader_source);

static void validate_shader(unsigned int shader_id);
static void validate_program(unsigned int program_id);

