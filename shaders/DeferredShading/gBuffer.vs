#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out VS_OUT
{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoord;
} vs_out;

layout(std140, binding = 0) uniform Matrices
{
	mat4 projection;
	mat4 view;
};

uniform mat4 model;
uniform mat3 NormalMatrix;

void main()
{
	gl_Position = projection * view * model * vec4(aPos,1.0f);

	vs_out.FragPos = vec3(model * vec4(aPos,1.0f));
	vs_out.Normal = NormalMatrix * aNormal;
	vs_out.TexCoord = aTexCoord;
}