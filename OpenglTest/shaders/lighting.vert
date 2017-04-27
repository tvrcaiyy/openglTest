#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 color;
layout (location = 1) in vec3 normal;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPos;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	Normal = normal;
	FragPos = vec3(model * vec4(position, 1.0f));
	ourColor = color;
	// We swap the y-axis by substracing our coordinates from 1. This is done because most images have the top y-axis inversed with OpenGL's top y-axis.
	// TexCoord = texCoord;
	// TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}