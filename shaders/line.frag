#version 330 core

out vec4 FragColor;

uniform vec3 new_color;

void main()
{
	FragColor = vec4(new_color, 1.0);
}
