#include "shader.h"



GLuint gen_shader(GLenum shader_type, char *source_name)
{

    unsigned int shader_id = glCreateShader(shader_type);


    FILE *file_pointer;
    printf("%s\n", source_name);
    file_pointer = fopen(source_name, "r");
    if(file_pointer == NULL) 
    {
        perror(strcat("Error while opening the file: ", source_name));
        return 0;
    }
    else 
    {
        //read file
        fseek(file_pointer, 0, SEEK_END);
        long fsize = ftell(file_pointer);
        fseek(file_pointer, 0, SEEK_SET);

        char *shader_source = malloc(fsize + 1);
        fread(shader_source, 1, fsize, file_pointer);

        shader_source[fsize] = '\0';
        //gen shader
        glShaderSource(shader_id, 1, &shader_source , NULL);
	    glCompileShader(shader_id);
        validate_shader(shader_id);
        free(shader_source);
    }
    fclose(file_pointer);
    return shader_id;   
}

static void validate_shader(unsigned int shader_id)
{
    GLint result = GL_FALSE;
	int info_log_lenght;

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_lenght);
	if ( info_log_lenght > 0 )
    {
		char *error_msg;
		glGetShaderInfoLog(shader_id, info_log_lenght, NULL, error_msg);
		printf("%s\n", error_msg);
	}
}

GLuint gen_shader_program(GLuint vs, GLuint gs, GLuint fs)
{

    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vs);
    if(gs != 0)
    {
        glAttachShader(program_id, gs);
    }
	glAttachShader(program_id, fs);
    glLinkProgram(program_id);
    validate_program(program_id);

    glDetachShader(program_id, vs);
    if(gs != 0)
    {
        glDetachShader(program_id, gs);
    }
	glDetachShader(program_id, fs);
	
	glDeleteShader(vs);
    if(gs != 0)
    {
        glDeleteShader(gs);
    }
	glDeleteShader(fs);
    return program_id;
}

static void validate_program(unsigned int program_id)
{
    GLint result = GL_FALSE;
	int info_log_lenght;

    glGetProgramiv(program_id, GL_LINK_STATUS, &result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_log_lenght);
	if ( info_log_lenght > 0 )
    {
		char *error_msg;
		glGetProgramInfoLog(program_id, info_log_lenght, NULL, error_msg);
		printf("%s\n", error_msg);
	}
}
