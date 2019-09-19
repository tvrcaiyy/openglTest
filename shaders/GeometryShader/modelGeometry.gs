#version 450 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 5) out;

in VS_OUT
{
	vec2 TexCoords;
	vec3 Normal;
} gs_in[];

out vec2 TexCoords;

uniform float time;
uniform int type;

vec3 getNormal(vec4 pt1,vec4 pt2,vec4 pt3)
{
	vec3 a = vec3(pt1 - pt2);
	vec3 b = vec3(pt3 - pt2);
	vec3 normal = normalize(cross(a,b));
	return normal;
}

void main()
{
	vec3 normal = getNormal(gl_in[0].gl_Position,gl_in[1].gl_Position,gl_in[2].gl_Position);

	float magnitude = 2;
	if(type == 1)
		magnitude = 0;

	TexCoords = gs_in[0].TexCoords;
	gl_Position = gl_in[0].gl_Position + vec4(normal * ((sin(time) + 1.0)/2.0 * magnitude) ,0.0);
	EmitVertex();

	TexCoords = gs_in[1].TexCoords;
	gl_Position = gl_in[1].gl_Position + vec4(normal * ((sin(time) + 1.0)/2.0 * magnitude) ,0.0);
	EmitVertex();

	TexCoords = gs_in[2].TexCoords;
	gl_Position = gl_in[2].gl_Position + vec4(normal * ((sin(time) + 1.0)/2.0 * magnitude) ,0.0);
	EmitVertex();

	EndPrimitive();
}