#include "camera.h"
#include <cglm/cglm.h>
#include "math_utils.h"




void init_camera(vec3 pos, vec3 dir)
{
    camera_position = pos;
    view_direction = dir;
}

