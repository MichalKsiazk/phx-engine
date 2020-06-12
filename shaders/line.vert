#version 400 core

uniform vec3 a_point;
uniform vec3 b_point;


out VS_OUT
{
	vec3 a_point;
	vec3 b_point;
} vs_out;

void main()
{
	gl_Position = vec4(0, 0, 0, 1.0);
	vs_out.a_point = a_point;
	vs_out.b_point = b_point;
}
