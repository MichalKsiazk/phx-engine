#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform vec2 scale;
uniform float aspect_ratio;
uniform vec2 position;

void main()
{
    gl_Position = vec4(aPos.x * scale.x * aspect_ratio + position.x, aPos.y * scale.y + position.y, aPos.z, 1.0);
    texCoord = aTexCoord;
}