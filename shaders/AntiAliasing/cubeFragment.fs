#version 450 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D textrue1;

void main()
{
	FragColor = texture(textrue1,TexCoords);
}