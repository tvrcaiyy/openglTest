////transform to tangent space
//#version 450 core
//
//in vec2 TexCoord;
//in vec3 tangentViewPos;
//in vec3 tangentLightPos;
//in vec3 tangentFragPos;
//
//out vec4 FragColor;
//
//uniform sampler2D texture1;
//uniform sampler2D normalTexture;
//
//void main()
//{
//    vec3 color = vec3(texture(texture1,TexCoord));
//    vec3 ambient = color * vec3(0.1);
//
//    vec3 normal = vec3(texture(normalTexture,TexCoord));
//    normal = normalize(normal * 2.0 - 1.0);
//
//    vec3 viewDir = normalize(tangentViewPos - tangentFragPos);
//    vec3 lightDir = normalize(tangentLightPos - tangentFragPos);
//
//    float diff = max(dot(lightDir,normal),0.0f);
//    vec3 diffuse = color * diff;
//
//    vec3 halfDir = normalize(viewDir + lightDir);
//    float spec = pow(max(dot(halfDir,normal),0.0f),32.0);
//    vec3 specular = vec3(1.0) * spec;
//
//    FragColor = vec4(ambient + diffuse + specular,1.0f);
//}

////transform to world space
#version 450 core

in vec2 TexCoord;
in vec3 FragPos;
in mat3 TBN;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform sampler2D texture1;
uniform sampler2D normalTexture;

void main()
{
    vec3 color = vec3(texture(texture1,TexCoord));
    vec3 ambient = color * vec3(0.1);

    vec3 normal = vec3(texture(normalTexture,TexCoord));
    normal = normalize(normal * 2.0 - 1.0);
    normal = normalize(TBN * normal);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(lightDir,normal),0.0f);
    vec3 diffuse = color * diff;

    vec3 halfDir = normalize(viewDir + lightDir);
    float spec = pow(max(dot(halfDir,normal),0.0f),32.0);
    vec3 specular = vec3(1.0) * spec;

    FragColor = vec4(ambient + diffuse + specular,1.0f);
    //FragColor = vec4(normal,1.0);
}