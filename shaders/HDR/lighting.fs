#version 450 core

in VS_OUT
{
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoord;
} fs_in;

out vec4 FragColor;

struct Lighting
{
    vec3 Position;
    vec3 Color;
};

uniform Lighting lightings[16];
uniform sampler2D texture1;
uniform vec3 viewPos;

void main()
{
    vec3 color = texture(texture1,fs_in.TexCoord).rgb;
    
    vec3 ambient = color * 0.0;
    
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.0);
    for(int i = 0;i < 16;i++)
    {
        vec3 lightDir = normalize(lightings[i].Position - fs_in.FragPos);
    
        float diff = max(dot(lightDir,normal),0.0);
        vec3 diffuse = diff * lightings[i].Color * color;
        vec3 result = diffuse;
        float distance = length(fs_in.FragPos - lightings[i].Position);
        result *= 1.0/(distance * distance);
        lightColor += result;
    }

    FragColor = vec4(ambient + lightColor,1.0);
}