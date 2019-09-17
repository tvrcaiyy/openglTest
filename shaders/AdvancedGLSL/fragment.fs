#version 450 core

in VS_OUT
{
	vec3 redColor;
	vec3 greenColor;
} fs_in;

out vec4 FragColor;


void main()
{
    //if(gl_FragCoord.x < 400)
    if(gl_FrontFacing)
        FragColor = vec4(fs_in.redColor,1.0);
    else
        FragColor = vec4(fs_in.greenColor,1.0);
}