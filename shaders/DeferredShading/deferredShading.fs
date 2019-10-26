#version 450 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform sampler2D albedospecTexture;
uniform int showType;
uniform vec3 viewPos;

struct Light
{
    vec3 Position;
    vec3 Color;

    float Linear;
    float Quadratic;
    float Constant;
    float Radius;
};

uniform Light lights[32];
uniform float exposure;
void main()
{
    vec3 FragPos = texture(positionTexture,TexCoord).rgb;
    vec3 Normal = texture(normalTexture,TexCoord).rgb;
    //vec4 albedospec = texture(albedospecTexture,TexCoord);
    vec3 color = texture(albedospecTexture,TexCoord).rgb;
    float Specular = texture(albedospecTexture,TexCoord).a;
    
    if(showType == 1)
    {
        FragColor = vec4(FragPos,1.0);
    }
    else if(showType == 2)
    {
        FragColor = vec4(Normal,1.0);
    }
    else if(showType == 3)
    {
        FragColor = vec4(color,1.0);
    }
    else if(showType == 4)
    {
        FragColor = vec4(Specular,Specular,Specular,1.0);
    }
    else
    {
        vec3 ambient = color * 0.1;
        vec3 light = vec3(0.0);

        for(int i = 0; i < 32;i++)
        {
            float distance = length(lights[i].Position - FragPos);
            if(distance < lights[i].Radius)
            {
                vec3 lightDir = normalize(lights[i].Position - FragPos);
                float diff = max(dot(lightDir,Normal),0.0);
                vec3 diffuse = diff * color * lights[i].Color;

                vec3 viewDir = normalize(viewPos - FragPos);
                vec3 halfwayDir = normalize(viewDir + lightDir);
                vec3 specular = pow(max(dot(halfwayDir,Normal),0.0),16.0) * color * Specular;

                float attenuation = 1.0/(lights[i].Constant + lights[i].Linear * distance + lights[i].Quadratic * distance * distance);
                diffuse *= attenuation;
                specular *= attenuation;
                light += diffuse + specular;
            }
        }

        vec3 result = vec3(1.0) - exp(-light * exposure);
        float gamma = 2.2;
        result = pow(result, vec3(1.0 / gamma));

        FragColor = vec4(result,1.0);
    }
}