


#version 400 core
layout (location = 0) in vec3 pos;


uniform mat4 view;
uniform mat4 projection;
uniform mat4 transformation;

uniform float scale;


out vec4 shader_source;


void main()
{
    gl_Position = projection * view * transformation  * vec4(pos.x * scale, pos.y * scale, pos.z * scale, 1.0);
    shader_source = vec4(pos, 1.0);
}






















































