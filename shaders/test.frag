#version 330 core
out vec4 FragColor;

in vec3 border_color;

void main()
{

    FragColor = vec4(border_color.x, border_color.y, border_color.z, 1.0);
} 
















