#version 450 core

in VS_OUT
{
    vec3 Normal;
    vec2 TexCoord;
    vec3 FragPos;
} fs_in;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1,fs_in.TexCoord);
}