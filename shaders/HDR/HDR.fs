#version 450 core

in VS_OUT
{
    vec2 TexCoord;
} fs_in;

out vec4 FragColor;

uniform sampler2D texture1;
uniform float exposure;

void main()
{
    const float gamma = 2.2;
    vec3 hdrColor = texture(texture1, fs_in.TexCoord).rgb;
    // reinhard
    //vec3 result = hdrColor / (hdrColor + vec3(1.0));
    // exposure
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
}