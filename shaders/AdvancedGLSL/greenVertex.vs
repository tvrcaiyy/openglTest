#version 450 core

layout(location = 0) in vec3 aPos;

out VS_OUT
{
	vec3 outerColor;
	vec3 innerColor;
} vs_out;

layout(std140, binding = 1) uniform Matries
{
	mat4 view;
	mat4 projection;	
};

uniform mat4 model;


void main()
{
	gl_Position = projection * view * model * vec4(aPos,1.0);
	gl_PointSize = gl_Position.z;
	vs_out.outerColor = vec3(0.0,1.0,0.0);
	vs_out.innerColor = vec3(0.0,1.0,0.0);
}