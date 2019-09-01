#version 450 core

in vec3 Normal;
in vec2 Texcoord;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 viewPos;

struct Light
{
    //vec3 direction;
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform Light light;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

void main()
{
    vec3 ambient = vec3(texture(material.diffuse,Texcoord)) * light.ambient;

    //vec3 lightDir = normalize(-light.direction);
    vec3 lightDir = normalize(light.position - FragPos);
    vec3 normal = normalize(Normal);
    float diff = max(dot(lightDir,normal),0.0f);
    vec3 diffuse = diff * vec3(texture(material.diffuse,Texcoord)) * light.diffuse;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = normalize(reflect(-lightDir,normal));
    float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
    vec3 specular = spec * (vec3(texture(material.specular,Texcoord))) * light.specular;

    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    ambient  *= attenuation;  
    diffuse   *= attenuation;
    specular *= attenuation; 

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result,1.0f);
}