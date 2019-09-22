#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
layout(std140,binding = 0) uniform Matrices
{
	mat4 view;
	mat4 projection;
};

void main()
{
	//gl_Position = projection * view * model * vec4(aPos,1.0f);
	gl_Position = vec4(aPos,1.0f);
	TexCoords = aTexCoords;
}