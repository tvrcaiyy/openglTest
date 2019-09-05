#version 450 core

in vec3 FragPos;
in vec3 Normal;
in vec2 Texcoord;

out vec4 FragColor;

struct DirLight
{
    vec3 lightDir;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 lightPos;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 lightPos;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

#define POINT_LIGHT_COUNT 4

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[POINT_LIGHT_COUNT];
uniform SpotLight spotLight;

vec3 calculateDirLight(vec3 norm,vec3 viewDir,DirLight dirLight);
vec3 calculatePointLight(vec3 norm,vec3 viewDir,PointLight pointLight,vec3 fragPos);
vec3 calculateSpotLight(vec3 norm,vec3 viewDir,SpotLight spotLight,vec3 fragPos);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = calculateDirLight(norm,viewDir,dirLight);
    for(int i = 0;i < POINT_LIGHT_COUNT;i++)
        result += calculatePointLight(norm,viewDir,pointLights[i],FragPos);
    
    result += calculateSpotLight(norm,viewDir,spotLight,FragPos);

    FragColor = vec4(result,1.0f);
}

vec3 calculateDirLight(vec3 norm,vec3 viewDir,DirLight light)
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,Texcoord).rgb);

    vec3 lightDir = normalize(light.lightDir);
    float diff = max(dot(-lightDir,norm),0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,Texcoord).rgb);

    vec3 reflect = reflect(lightDir,norm);
    float spec = pow(max(dot(reflect,viewDir),0.0f),material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular,Texcoord).rgb);

    return ambient + diffuse + specular;
}

vec3 calculatePointLight(vec3 norm,vec3 viewDir,PointLight light,vec3 fragPos)
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,Texcoord).rgb);

    vec3 lightDir = normalize(fragPos - light.lightPos);
    float diff = max(dot(-lightDir,norm),0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,Texcoord).rgb);

    vec3 reflect = reflect(lightDir,norm);
    float spec = pow(max(dot(reflect,viewDir),0.0f),material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular,Texcoord).rgb);

    float distance = distance(light.lightPos , fragPos);
    float attenuation = 1.0f/(light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

vec3 calculateSpotLight(vec3 norm,vec3 viewDir,SpotLight light,vec3 fragPos)
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,Texcoord).rgb);

    vec3 lightDir = normalize(fragPos - light.lightPos);
    float diff = max(dot(-lightDir,norm),0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,Texcoord).rgb);

    vec3 reflect = reflect(lightDir,norm);
    float spec = pow(max(dot(reflect,viewDir),0.0f),material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular,Texcoord).rgb);

    float theta = dot(lightDir,light.direction);
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon,0.0f,1.0f);
    ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;

    float distance = length(light.lightPos - fragPos);
    float attenuation = 1.0f/(light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}