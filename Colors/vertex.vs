#version 450 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;
out vec3 lightPos;
out vec4 GouraudColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform vec3 LightPosition;

uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 viewPos;

void main()
{
	gl_Position = projection * view * model * vec4(aPos,1.0f);
	Normal = normalMatrix * aNormal;
	FragPos = vec3(model * vec4(aPos,1));
	//lightPos = vec3(view * vec4(LightPosition,1.0f));
	lightPos = LightPosition;




	float ambientStrength = 0.1f;
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
    GouraudColor = vec4(result,1.0f);
}