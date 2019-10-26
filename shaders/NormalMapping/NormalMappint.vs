//transform to tangent space
//#version 450 core
//layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aNormal;
//layout(location = 2) in vec2 aTexCoord;
//layout(location = 3) in vec3 aTangent;
//layout(location = 4) in vec3 aBitangent;
//
//out vec2 TexCoord;
//out vec3 tangentViewPos;
//out vec3 tangentLightPos;
//out vec3 tangentFragPos;
//
//layout(std140, binding = 0) uniform Matrices
//{
//	mat4 projection;
//	mat4 view;
//};
//uniform mat4 model;
//uniform mat3 NormalMatrix;
//uniform vec3 viewPos;
//uniform vec3 lightPos;
//
//void main()
//{
//	gl_Position = projection * view * model * vec4(aPos,1.0f);
//	TexCoord = aTexCoord;
//	vec3 FragPos = vec3(model * vec4(aPos,0.0f));
//
//	vec3 T = normalize(NormalMatrix * aTangent);
//	vec3 B = normalize(NormalMatrix * aBitangent);
//	vec3 N = normalize(NormalMatrix * aNormal);
//
//	mat3 TBN = mat3(T,B,N);
//	TBN = transpose(TBN);
//	tangentViewPos = TBN * viewPos;
//	tangentLightPos = TBN * lightPos;
//	tangentFragPos = TBN * FragPos;
//}


////transform to world space
#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 aTangent;
layout(location = 4) in vec3 aBitangent;

out vec2 TexCoord;
out vec3 FragPos;
out mat3 TBN;

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
	TexCoord = aTexCoord;
	FragPos = vec3(model * vec4(aPos,0.0f));

	vec3 T = normalize(NormalMatrix * aTangent);
	//vec3 B = normalize(NormalMatrix * aBitangent);
	vec3 N = normalize(NormalMatrix * aNormal);
	T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);


	TBN = mat3(T,B,N);
}