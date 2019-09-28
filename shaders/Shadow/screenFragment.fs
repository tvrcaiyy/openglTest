#version 450 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D screenTexture;

void main()
{
    float depth = texture(screenTexture,TexCoord).r;
    FragColor = vec4(vec3(depth),1.0f);
}