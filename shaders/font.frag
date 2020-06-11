#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D ourTexture;

uniform vec2 texture_shift;

uniform vec4 color;

void main()
{

    vec4 tc = texture(ourTexture, texCoord) * color;
    if(tc.a < 0.9)
        discard;
    FragColor = tc;
} 
