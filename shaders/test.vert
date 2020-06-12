#version 400 core
layout (location = 0) in vec2 aPos;

uniform vec3 position;
uniform float radius;

uniform mat4 transformation;

uniform vec3 border_color;

out VS_OUT
{
    float radius;
    vec3 border_color;
    mat4 transformation;
} vs_out;

void main()
{
    gl_Position = vec4(0, 0, 0, 1.0);
    vs_out.radius = float(radius);
    vs_out.border_color = border_color;
    vs_out.transformation = transformation;
}
















