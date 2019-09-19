#version 450 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;

out VS_OUT
{
	vec3 color;
} vs_out;

layout(std140, binding=1) uniform Matrices
{
	mat4 view;
	mat4 projection;
};

uniform mat4 model;

void main()
{
	gl_PointSize = 10;
	gl_Position = projection * view * model * vec4(aPos,0.0,1.0);
	vs_out.color = aColor;
}