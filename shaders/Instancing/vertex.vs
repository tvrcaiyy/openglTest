#version 450 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aOffset;

out vec3 fColor;

layout(std140,binding = 1) uniform Matrices
{
	mat4 view;
	mat4 projection;
};
uniform mat4 model;

//uniform vec2 offsets[100];

void main()
{
	fColor = aColor;
	//vec2 offset = offsets[gl_InstanceID];
    gl_Position = vec4(aPos * gl_InstanceID / 100 + aOffset,0.0,1.0);
}