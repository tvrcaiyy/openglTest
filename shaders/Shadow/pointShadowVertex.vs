#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;

layout(std140, binding = 0) uniform Matrices
{
	mat4 view;
	mat4 projection;
};

void main()
{
	gl_Position = model * vec4(aPos,1.0f);
}