#version 400 core

layout (points) in;
layout (line_strip, max_vertices = 2) out;


in VS_OUT
{
	vec3 a_point;
	vec3 b_point;
} gs_in[];

uniform float aspect_ratio;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	vec4 pos1 = projection * view * vec4(gs_in[0].a_point, 1.0);
	gl_Position = pos1;
	EmitVertex();

	vec4 pos2 = projection * view * vec4(gs_in[0].b_point, 1.0);
	gl_Position = pos2;
	EmitVertex();
	EndPrimitive();
}
