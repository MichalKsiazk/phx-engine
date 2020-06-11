

#version 330 core
out vec4 FragColor;

uniform vec3 new_color;

in vec4 shader_source;

void main()
{
    float r = new_color.x;
    float g = new_color.y;
    float b = new_color.z;

    float shadow_r = r + (r * (shader_source.z / 4));
    float shadow_g = g + (g * (shader_source.z / 4));
    float shadow_b = b + (b * (shader_source.z / 4));

    FragColor = vec4(shadow_r, shadow_g, shadow_b, 1.0);
} 



















































































