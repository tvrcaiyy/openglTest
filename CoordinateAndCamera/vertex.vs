#version 450 core
layout(location = 0) in vec3 Pos;
layout(location = 1) in vec2 TexCoord;

out vec3 ourColor;
out vec2 ourTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(Pos,1.0f);
	ourTexCoord = TexCoord;
}