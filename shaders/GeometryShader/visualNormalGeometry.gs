#version 450 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in VS_OUT
{
	vec2 TexCoords;
	vec3 Normal;
} gs_in[];

void main()
{
	vec3 normal = normalize(gs_in[0].Normal);
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
	gl_Position = gl_in[0].gl_Position; + vec4(normal * 0.2 ,0.0);
	EmitVertex();
	EndPrimitive();

	normal = normalize(gs_in[1].Normal);
	gl_Position = gl_in[1].gl_Position;
	EmitVertex();
	gl_Position = gl_in[1].gl_Position + vec4(normal * 0.2 ,0.0);
	EmitVertex();
	EndPrimitive();

	normal = normalize(gs_in[2].Normal);
	gl_Position = gl_in[2].gl_Position;
	EmitVertex();
	gl_Position = gl_in[2].gl_Position + vec4(normal * 0.2 ,0.0);
	EmitVertex();
	EndPrimitive();
}