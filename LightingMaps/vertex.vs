#version 450 core
layout(location = 0)in vec3 aPos;
layout(location = 1)in vec3 aNormal;
layout(location = 2)in vec2 aTexcoord;

out vec3 Normal;
out vec2 Texcoord;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;

void main()
{
	gl_Position = projection * view * model * vec4(aPos,1.0f);
	Normal = normalMatrix * aNormal;
	Texcoord = aTexcoord;
	FragPos = vec3(model * vec4(aPos,1.0f));
}
