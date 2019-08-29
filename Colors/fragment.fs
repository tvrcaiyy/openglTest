#version 450 core

uniform vec3 lightColor;
uniform vec3 objectColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(objectColor * objectColor,1.0f);
}