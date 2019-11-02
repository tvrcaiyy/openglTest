#version 450 core

layout(location = 0) out vec3 gNormal;
layout(location = 1) out vec3 gAlbedoSpec;
layout(location = 2) out vec4 gPosition;

in VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
} fs_in;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

const float NEAR = 0.1; // 投影矩阵的近平面
const float FAR = 50.0f; // 投影矩阵的远平面
float linearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;//to NDC
    return (2.0 * NEAR * FRA) / (FAR + NEAE - z * (FAR - NEAR));
}

void main()
{
    gPosition.xyz = fs_in.FragPos;
    gPosition.z = linearizeDepth(gl_fragCoord.z);
    gNormal = normalize(fs_in.Normal);
    gAlbedoSpec.rgb = vec3(0.95);//texture(texture_diffuse1, fs_in.TexCoord).rgb;
}