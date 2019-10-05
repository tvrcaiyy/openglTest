#version 450 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float far_plane;


uniform sampler2D texture1;
uniform samplerCube shadowTexture;

float IsInShadow(vec3 fragPos)
{
    vec3 fragToLight = fragPos - lightPos;
    float currentDepth = length(fragToLight);
    float bias = max(0.05 * (1.0 - dot(Normal,normalize(-fragToLight))),0.005);
    
    vec3 sampleOffsetDirections[20] = vec3[]
    (
       vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
       vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
       vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
       vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
       vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
    );
    float shadow = 0.0;
    for(int i = 0;i < 20;i++)
    {
        float closestDepth = texture(shadowTexture,fragToLight + sampleOffsetDirections[i] * 0.05).r;
        closestDepth *= far_plane;
        if(currentDepth - bias > closestDepth)
            shadow += 1.0f;
    }
    shadow /= 20.0f;
    return shadow;
}

void main()
{
    vec3 color = vec3(texture(texture1,TexCoord));
    vec3 normal = normalize(Normal);
    float shadow = IsInShadow(FragPos);

    vec3 ambient = vec3(0.3) * color;

    vec3 lightDir = normalize(lightPos - FragPos);
    
    float diff = max(dot(lightDir,normal),0.0f);
    vec3 diffuse = (1-shadow) * diff * color;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(halfDir,normal),0.0f),32.0);
    vec3 specular = (1-shadow) * spec * vec3(0.3);

    
    FragColor = vec4(ambient + diffuse + specular,1.0f);
}


//#version 450 core
//
//in vec2 TexCoord;
//in vec3 Normal;
//in vec3 FragPos;
//
//out vec4 FragColor;
//
//uniform vec3 lightPos;
//uniform vec3 lightDir;
//uniform vec3 viewPos;
//
//uniform sampler2D texture1;
//uniform samplerCube shadowTexture;
//uniform float far_plane;
//
//float IsInShadow(vec3 fragPos)
//{
//    // get vector between fragment position and light position
//    vec3 fragToLight = fragPos - lightPos;
//    // ise the fragment to light vector to sample from the depth map    
//    //float closestDepth = texture(shadowTexture, fragToLight).r;
//    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
//    //closestDepth *= far_plane;
//    // now get current linear depth as the length between the fragment and light position
//    float currentDepth = length(fragToLight);
//    // test for shadows
//    // we use a much larger bias since depth is now in [near_plane, far_plane] range
//    float bias = max(0.05 * (1.0 - dot(Normal, normalize(-fragToLight))), 0.005);
//    //float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;        
//    // display closestDepth as debug (to visualize depth cubemap)
//    //FragColor = vec4(vec3(closestDepth / far_plane), 1.0);    
//    
//    vec3 sampleOffsetDirections[20] = vec3[]
//    (
//       vec3( 1,  1,  1), vec3( 1, -1,  1), vec3(-1, -1,  1), vec3(-1,  1,  1), 
//       vec3( 1,  1, -1), vec3( 1, -1, -1), vec3(-1, -1, -1), vec3(-1,  1, -1),
//       vec3( 1,  1,  0), vec3( 1, -1,  0), vec3(-1, -1,  0), vec3(-1,  1,  0),
//       vec3( 1,  0,  1), vec3(-1,  0,  1), vec3( 1,  0, -1), vec3(-1,  0, -1),
//       vec3( 0,  1,  1), vec3( 0, -1,  1), vec3( 0, -1, -1), vec3( 0,  1, -1)
//    );
//    float shadow = 0.0;
//    for(int i = 0;i < 20;i++)
//    {
//        float closestDepth = texture(shadowTexture, fragToLight + sampleOffsetDirections[i] * 0.05).r;
//        closestDepth *= far_plane;
//        if(currentDepth -  bias > closestDepth)   
//            shadow += 1.0;
//    }
//    shadow /= 20.0f;
//        
//    return shadow;
//}
//
//void main()
//{
//    float shadow = IsInShadow(FragPos);
//    vec3 color = vec3(texture(texture1,TexCoord));
//    vec3 ambient = vec3(0.3) * color;
//
//    vec3 normal = normalize(Normal);
//    vec3 viewDir = normalize(viewPos - FragPos);
//    vec3 lightDir = normalize(lightPos - FragPos);
//    //vec3 lightDir = normalize(lightDir);
//    float diff = max(dot(lightDir,normal),0.0f);
//    vec3 diffuse = (1 - shadow) * diff * color;
//
//    float spec = 0.0;
//    vec3 halfDir = normalize(viewDir + lightDir);
//    spec = pow(max(dot(halfDir,normal),0.0),32.0);
//    vec3 specular = (1 - shadow) * vec3(0.3) * spec;
//    color = ambient + diffuse + specular;
//    
//    FragColor = vec4(ambient + diffuse + specular, 1.0);
//    
//}