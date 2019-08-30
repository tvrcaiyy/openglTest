#version 450 core

in vec3 Normal;
in vec3 FragPos;
in vec3 lightPos;
in vec4 GouraudColor;

out vec4 FragColor;

//uniform vec3 lightColor;
//uniform vec3 objectColor;
//uniform vec3 viewPos;

void main()
{
    /*float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 normal = normalize(Normal);
    float diff = max(dot(lightDir,normal),0.0f);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0f),32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor; 
    FragColor = vec4(result,1.0f);*/

    FragColor = GouraudColor;
}