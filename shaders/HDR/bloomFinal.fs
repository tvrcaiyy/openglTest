#version 450 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D blurTexture;
uniform float exposure;
void main()
{
    vec3 color = texture(texture1,TexCoord).rgb + texture(blurTexture,TexCoord).rgb;
    
    vec3 result = vec3(1.0) - exp(-color * exposure);
    const float gamma = 2.2;
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result,1.0);
}