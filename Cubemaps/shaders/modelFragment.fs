#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_reflect1;
uniform samplerCube texture1;

uniform vec3 viewPos;

void main()
{    
    vec3 viewDir = normalize(FragPos - viewPos);
    vec3 normal = normalize(Normal);
    vec3 reflectDir = reflect(viewDir,normal);
    vec3 reflectTexture = vec3(texture(texture_reflect1,TexCoords));
    vec3 reflecSkyTexture = vec3(texture(texture1, reflectDir));
    vec3 reflecResult = reflecSkyTexture * reflectTexture;

    //float diff = max(normalize(dot(viewDir,normal)),0);
    vec3 diffuseTexture = vec3(texture(texture_diffuse1, TexCoords));

    FragColor = vec4(diffuseTexture + reflecResult,1.0);
    //FragColor = vec4(reflecResult,1.0);
    //FragColor = texture(texture_diffuse1, TexCoords);
}