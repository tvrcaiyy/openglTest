#version 450 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform samplerCube texture1;
uniform vec3 viewPos;

void main()
{    
    vec3 viewDir = normalize(FragPos - viewPos);
    //vec3 reflectDir = reflect(viewDir,normalize(Normal));
    //FragColor = texture(texture1, reflectDir);

    float ratio = 1.0/1.52;
    vec3 refractDir = refract(viewDir,normalize(Normal),ratio);
    FragColor = texture(texture1, refractDir);
}