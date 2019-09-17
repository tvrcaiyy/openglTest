#version 450 core

layout(location = 0) in vec3 aPos;

out VS_OUT
{
	vec3 redColor;
	vec3 greenColor;
} vs_out;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos,1.0);
	gl_PointSize = gl_Position.z;
	vs_out.redColor = vec3(1.0,0.0,0.0);
	vs_out.greenColor = vec3(0.0,1.0,0.0);
}