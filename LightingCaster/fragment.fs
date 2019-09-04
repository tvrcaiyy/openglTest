#version 450 core

in vec3 Normal;
in vec2 Texcoord;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 viewPos;

//struct Light
//{
//    //vec3 direction;
//    vec3 position;
//
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//
//    float constant;
//    float linear;
//    float quadratic;
//};
//uniform Light light;

struct SpotLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

    vec3 direction;
    float cutOff;
    float outCutOff;
};
uniform SpotLight light;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform Material material;

//Point Light
//void main()
//{
//    vec3 ambient = vec3(texture(material.diffuse,Texcoord)) * light.ambient;
//
//    //vec3 lightDir = normalize(-light.direction);
//    vec3 lightDir = normalize(light.position - FragPos);
//    vec3 normal = normalize(Normal);
//    float diff = max(dot(lightDir,normal),0.0f);
//    vec3 diffuse = diff * vec3(texture(material.diffuse,Texcoord)) * light.diffuse;
//
//    vec3 viewDir = normalize(viewPos - FragPos);
//    vec3 reflectDir = normalize(reflect(-lightDir,normal));
//    float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
//    vec3 specular = spec * (vec3(texture(material.specular,Texcoord))) * light.specular;
//
//    float distance    = length(light.position - FragPos);
//    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
//
//    ambient  *= attenuation;  
//    diffuse   *= attenuation;
//    specular *= attenuation; 
//
//    vec3 result = ambient + diffuse + specular;
//    FragColor = vec4(result,1.0f);
//}

//Spotlight without smooth
//void main()
//{
//    vec3 lightDir = normalize(light.position - FragPos);
//    float theta = dot(lightDir,normalize(-light.direction));
//
//    if(theta > light.cutOff)
//    {
//        vec3 ambient = light.ambient * vec3(texture(material.diffuse,Texcoord));
//
//        vec3 normal = normalize(Normal);
//        float diff = max(dot(lightDir,normal),0);
//        vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,Texcoord));
//
//        vec3 reflect = reflect(-lightDir,normal);
//        float spec = pow(max(dot(reflect,normal),0.0f),material.shininess);
//        vec3 specular = light.specular * spec * vec3(texture(material.specular,Texcoord));
//
//        float distance = distance(light.position,FragPos);
//        float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
//        ambient *= attenuation;
//        diffuse *= attenuation;
//        specular *= attenuation;
//
//        vec3 result = ambient + diffuse + specular;
//        FragColor = vec4(result,1.0f);
//    }
//    else
//    {
//        FragColor = vec4(light.ambient * vec3(texture(material.diffuse,Texcoord)).rgb,1.0f);
//    }
//}

//Spotlight with smooth
void main()
{
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,Texcoord).rgb);

    vec3 lightDir = normalize(light.position - FragPos);
    vec3 normal = normalize(Normal);
    float diff = max(dot(lightDir,normal),0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,Texcoord).rgb);

    vec3 reflect = reflect(-lightDir,normal);
    float spec = pow(max(dot(reflect,normal),0.0f),material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular,Texcoord).rgb);

    float theta = dot(-lightDir,light.direction);
    float epsilon = light.cutOff - light.outCutOff;
    float intensity = clamp((theta - light.outCutOff) / epsilon,0.0f,1.0f);
    //ambient *= intensity;
    diffuse *= intensity;
    specular *= intensity;

    float distance = distance(light.position, FragPos);
    float attenuation = 1.0f/(light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result,1.0f);

    

}
