#version 450 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec4 FragPosInLightSpace;

out vec4 FragColor;

struct Lighting
{
    //vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quaratic;
};
uniform Lighting lighting;

struct Material
{
    float shininess;
};
uniform Material material;

uniform vec3 lightPos;
uniform vec3 lightDir;
uniform vec3 viewPos;

uniform sampler2D texture1;
uniform sampler2D shadowTexture;

float IsInShadow()
{
    vec3 lightCoord = FragPosInLightSpace.xyz / FragPosInLightSpace.w;
    lightCoord = lightCoord * 0.5 + 0.5;
    
    //float bias = 0.005;
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    float shadow = 0.0;
    vec2  textureSize = textureSize(shadowTexture,0);
    for(int i = -2;i <= 2;i++)
    {
        for(int j = -2;j <= 2;j++)
        {
            vec2 offset = vec2(i,j) / textureSize;
            float closestDepth = texture(shadowTexture,lightCoord.xy + offset).r;
            shadow += lightCoord.z - bias > closestDepth ? 1.0 : 0.0;
        }   
    }
    shadow = shadow / 25.0;
    //float closestDepth = texture(shadowTexture,lightCoord.xy).r;
    //    shadow = lightCoord.z - bias > closestDepth ? 1.0 : 0.0;
    if(lightCoord.z > 1.0)
        shadow = 0.0;
    return shadow;
}

void main()
{
    float shadow = IsInShadow();

    vec3 color = vec3(texture(texture1,TexCoords));
    vec3 ambient = lighting.ambient * color;

    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 lightDir = normalize(lightPos - FragPos);
    //vec3 lightDir = normalize(lightDir);
    float diff = max(dot(lightDir,normal),0.0f);
    vec3 diffuse = (1 - shadow) * diff * color;

    float spec = 0.0;
    vec3 halfDir = normalize(viewDir + lightDir);
    spec = pow(max(dot(halfDir,normal),0.0),32.0);
    vec3 specular = (1 - shadow) * vec3(0.3) * spec;
    color = ambient + diffuse + specular;
    color = pow(color,vec3(1/2.2));
    
    FragColor = vec4(ambient + diffuse + specular, 1.0);
}