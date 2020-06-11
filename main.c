#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "phx_engine.h"
#include "phx_config.h"
#include "model_loader.h"




 
int main(int argc, char** argv)
{
    printf("%s\n", "PROGRAM INIT");
    if(!glfwInit())
    {
        printf("%s", "GLFW ERROR");
        return 1;
    }   
    GLFWwindow* window = glfwCreateWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_TITLE, NULL, NULL); 
    glfwMakeContextCurrent(window);
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return 1;
    }

    init_engine(window);
    return 0;
}
