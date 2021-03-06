#version 450 core

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

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
uniform vec3 lightPos;
uniform Material material;
uniform sampler2D texture1;
uniform vec3 viewPos;
uniform bool blinn;
uniform bool gamma;
void main()
{
    vec3 color = vec3(texture(texture1,TexCoords));
    vec3 ambient = lighting.ambient * color;

    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(lightDir,normal),0.0f);
    vec3 diffuse = diff * color;

    float spec = 0.0;
    if(blinn)
    {
        vec3 halfDir = normalize(viewDir + lightDir);
        spec = pow(max(dot(halfDir,normal),0.0),32.0);
    }
    else
    {
        vec3 reflectDir = reflect(-lightDir,normal);
        spec = pow(max(dot(viewDir,reflectDir),0.0f),8.0);
    }
    vec3 specular = vec3(0.3) * spec;
    color = ambient + diffuse + specular;
    color = pow(color,vec3(1/2.2));
    if(gamma)
        FragColor = vec4(color,1.0);
    else
        FragColor = vec4(ambient + diffuse + specular, 1.0);
}

//#version 450 core
//out vec4 FragColor;
//
//in vec3 FragPos;
//in vec3 Normal;
//in vec2 TexCoords;
//
//uniform sampler2D floorTexture;
//uniform vec3 lightPos;
//uniform vec3 viewPos;
//uniform bool blinn;
//
//void main()
//{           
//    vec3 color = texture(floorTexture, TexCoords).rgb;
//    // ambient
//    vec3 ambient = 0.05 * color;
//    // diffuse
//    vec3 lightDir = normalize(lightPos - FragPos);
//    vec3 normal = normalize(Normal);
//    float diff = max(dot(lightDir, normal), 0.0);
//    vec3 diffuse = diff * color;
//    // specular
//    vec3 viewDir = normalize(viewPos - FragPos);
//    vec3 reflectDir = reflect(-lightDir, normal);
//    float spec = 0.0;
//    if(blinn)
//    {
//        vec3 halfwayDir = normalize(lightDir + viewDir);  
//        spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
//    }
//    else
//    {
//        vec3 reflectDir = reflect(-lightDir, normal);
//        spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
//    }
//    vec3 specular = vec3(0.3) * spec; // assuming bright white light color
//    FragColor = vec4(ambient + diffuse + specular, 1.0);
//}