#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
layout(std140,binding = 0) uniform Matrices
{
	mat4 view;
	mat4 projection;
};

uniform mat3 normalMatrix;

void main()
{
	gl_Position = projection * view * model * vec4(aPos,1.0f);
	TexCoords = aTexCoords;
	Normal = normalMatrix * aNormal;
	FragPos = vec3(model * vec4(aPos,1.0));
}