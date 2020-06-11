#version 400 core
layout (points) in;
layout (line_strip, max_vertices = 400) out;

in VS_OUT {
    float radius;
    vec3 border_color;
    mat4 transformation;
} gs_in[];

out vec3 border_color;

float resolution = 20;

float step_angle = 360 / resolution;

float current_angle = 0;

float radius = gs_in[0].radius;


uniform float aspect_ratio;
uniform mat4 projection;
uniform mat4 view;

void main() 
{

    border_color = gs_in[0].border_color;

    for(int i = 0; i <= resolution; i += 1)
    {
        float x1 = sin(radians(current_angle)) * radius;
        float y1 = cos(radians(current_angle)) * radius;

        vec4 pos1 = projection * view * gs_in[0].transformation * (vec4(x1, y1, 0.0, 1.0));

        gl_Position = pos1;// * vec4(gs_in[0].aspect_ratio, 0);

        EmitVertex();
        float x2 = sin(radians(current_angle)) * radius;
        float y2 = cos(radians(current_angle)) * radius;

        vec4 pos2 = projection * view * gs_in[0].transformation * (vec4(x2, y2, 0.0, 1.0));

        gl_Position = pos2;// * vec4(gs_in[0].aspect_ratio, 0);
        EmitVertex();
        current_angle += step_angle;
    } 
    for(int i = 0; i <= resolution; i += 1)
    {
        float z1 = sin(radians(current_angle)) * radius;
        float y1 = cos(radians(current_angle)) * radius;

        vec4 pos1 = projection * view * gs_in[0].transformation * (vec4(0, y1, z1, 1.0));

        gl_Position = pos1;// * vec4(gs_in[0].aspect_ratio, 0);

        EmitVertex();
        float z2 = sin(radians(current_angle)) * radius;
        float y2 = cos(radians(current_angle)) * radius;

        vec4 pos2 = projection * view * gs_in[0].transformation * (vec4(0, y2, z2, 1.0));

        gl_Position = pos2;// * vec4(gs_in[0].aspect_ratio, 0);
        EmitVertex();
        current_angle += step_angle;
    }   
    for(int i = 0; i <= resolution; i += 1)
    {
        float z1 = sin(radians(current_angle)) * radius;
        float x1 = cos(radians(current_angle)) * radius;

        vec4 pos1 = projection * view * gs_in[0].transformation * (vec4(x1, 0.0, z1, 1.0));

        gl_Position = pos1;// * vec4(gs_in[0].aspect_ratio, 0);

        EmitVertex();
        float z2 = sin(radians(current_angle)) * radius;
        float x2 = cos(radians(current_angle)) * radius;

        vec4 pos2 = projection * view * gs_in[0].transformation * (vec4(x2, 0.0, z2, 1.0));

        gl_Position = pos2;// * vec4(gs_in[0].aspect_ratio, 0);
        EmitVertex();
        current_angle += step_angle;
    }   
    EndPrimitive();

    
}  