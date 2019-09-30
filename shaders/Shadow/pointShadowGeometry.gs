#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 18) out;

uniform mat4 shadowMatrices[6];

out vec4 FragPos;

void main()
{
	for(int face = 0;face < 6;face++)
	{
		gl_layer = face;
		for(int j = 0;j < 3;j++)
		{
			FragPos = gl_in[j];
			glPosition = shadowMatrices[face] * FragPos;
			EmitVertex();
		}
		EndPrimitive();
	}
}