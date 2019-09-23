#version 450 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D textrue1;

void main()
{
    float depth = texture(textrue1,TexCoords).r;
	FragColor = vec4(vec3(depth),1.0);
    //FragColor = vec4(vec3(1.0,0.0,0.0),1.0);
}