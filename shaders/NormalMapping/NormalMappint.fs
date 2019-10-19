#version 450 core

in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D normalTexture;

void main()
{
    FragColor = texture(texture1,TexCoord);
}