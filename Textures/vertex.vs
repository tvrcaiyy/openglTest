#version 450 core
layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCrood;

out vec3 outColor;
out vec2 outTexCrood;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * transform * vec4(Pos,1.0);
	outColor = Color;
	outTexCrood = TexCrood;
}