#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out VS_OUT
{
	vec3 Normal;
	vec2 TexCoord;
	vec3 FragPos;
	vec4 FragPosInLightSpace;
} vs_out;

uniform mat4 model;
uniform mat3 normalMatrix;
uniform mat4 lightSpaceMatrix;

layout(std140,binding = 0) uniform Matrices
{
	mat4 view;
	mat4 projection;
};

void main()
{
	gl_Position = projection * view * model * vec4(aPos,1.0);
	vs_out.Normal = normalMatrix * aNormal;
	vs_out.TexCoord = aTexCoord;
	vs_out.FragPos = vec3(model * vec4(aPos,1.0));
	vs_out.FragPosInLightSpace = lightSpaceMatrix * model * vec4(aPos,1.0);
}

//#version 450 core
//
//layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aNormal;
//layout(location = 2) in vec2 aTexCoords;
//
//out vec2 TexCoords;
//out vec3 Normal;
//out vec3 FragPos;
//out vec4 FragPosInLightSpace;
//
//uniform mat4 model;
//layout(std140,binding = 0) uniform Matrices
//{
//	mat4 view;
//	mat4 projection;
//};
//
//uniform mat3 normalMatrix;
//uniform mat4 lightSpaceMatrix;
//
//void main()
//{
//	gl_Position = projection * view * model * vec4(aPos,1.0f);
//	TexCoords = aTexCoords;
//	Normal = normalMatrix * aNormal;
//	FragPos = vec3(model * vec4(aPos,1.0));
//	FragPosInLightSpace = lightSpaceMatrix * vec4(FragPos,1.0);
//}