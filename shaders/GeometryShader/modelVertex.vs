#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT
{
	vec2 TexCoords;
	vec3 Normal;
} vs_out;

uniform mat4 model;
layout(std140, binding=1) uniform Matrices
{
	mat4 view;
	mat4 projection;
};

void main()
{
    vs_out.TexCoords = aTexCoords;
	vs_out.Normal = aNormal;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}