#include "utils.h"



void init_counter()
{
    fps = 0;
    last_time = glfwGetTime();
    c_fps = 0;
}

void count_fps()
{
    fps++;
    double current_time = glfwGetTime();

    char buffer[5];
    sprintf(buffer, "%d", c_fps);
    bmfont_render_string(buffer, 0.02, -0.97, 0.97);
    if(current_time - last_time >= 1.0)
    {
        last_time = current_time;
        c_fps = fps;
        fps = 0;

    }


}
