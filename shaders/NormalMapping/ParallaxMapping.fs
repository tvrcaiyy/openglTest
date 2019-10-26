//transform to tangent space
#version 450 core

in vec2 TexCoord;
in vec3 tangentViewPos;
in vec3 tangentLightPos;
in vec3 tangentFragPos;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D normalTexture;
uniform sampler2D depthTexture;
uniform float height_scale;
uniform int parallaxType;
uniform float maxLayer;

vec2 simpleParallax(vec2 texCoord, vec3 viewDir)
{
    float height = vec3(texture(depthTexture,texCoord)).r;
    //vec2 p = viewDir.xy / viewDir.z * height * height_scale;
    vec2 p = viewDir.xy * height * height_scale;
    vec2 currentTexCoord = texCoord - p;
    return currentTexCoord;
}
vec2 steepParallax(vec2 texCoord, vec3 viewDir)
{
    const float minLayer = 8.0;
    //const float maxLayer = 32.0;
    float layerCount = mix(maxLayer,minLayer,abs(dot(vec3(0.0,0.0,1.0),viewDir)));

    //vec2 p = viewDir.xy / viewDir.z * height_scale;
    vec2 p = viewDir.xy * height_scale;
    vec2 texCoordDelta = p / layerCount;
    float depthDelta = 1.0 / layerCount;

    float currentLayerDepth = 0;
    vec2 currentTexCoord = texCoord;
    float currentMapDepth = vec3(texture(depthTexture,currentTexCoord)).r;

    while(currentLayerDepth < currentMapDepth)
    {
        currentLayerDepth += depthDelta;
        currentTexCoord -= texCoordDelta;
        currentMapDepth = vec3(texture(depthTexture,currentTexCoord)).r;
    }
    return currentTexCoord;
}
vec2 parallaxOcclusion(vec2 texCoord, vec3 viewDir)
{
    //same with steep Parallax
    const float minLayer = 8.0;
    const float maxLayer = 32.0;
    float layerCount = mix(maxLayer,minLayer,abs(dot(vec3(0.0,0.0,1.0),viewDir)));

    //vec2 p = viewDir.xy / viewDir.z * height_scale;
    vec2 p = viewDir.xy * height_scale;
    vec2 texCoordDelta = p / layerCount;
    float depthDelta = 1.0 / layerCount;

    float currentLayerDepth = 0;
    vec2 currentTexCoord = texCoord;
    float currentMapDepth = vec3(texture(depthTexture,currentTexCoord)).r;

    while(currentLayerDepth < currentMapDepth)
    {
        currentLayerDepth += depthDelta;
        currentTexCoord -= texCoordDelta;
        currentMapDepth = vec3(texture(depthTexture,currentTexCoord)).r;
    }
    //new code
    vec2 prevTexCoord = currentTexCoord + texCoordDelta;
    float prevLayerDepth = currentLayerDepth - depthDelta;
    float currentDepthDelta = currentMapDepth - currentLayerDepth;
    float prevDepthDelta = vec3(texture(depthTexture,prevTexCoord)).r - prevLayerDepth;

    float weight = currentDepthDelta / (currentDepthDelta - prevDepthDelta);
    vec2 finalTexCoord  = prevTexCoord * weight + currentTexCoord * (1 - weight);
    return finalTexCoord;
}

vec2 parallaxMapping(vec2 texCoord, vec3 viewDir)
{
    vec2 finalTexCoord;
    if(parallaxType == 1)//simple Parallax mapping
    {
        finalTexCoord = simpleParallax(texCoord,viewDir);
    }
    else if(parallaxType == 2)//steep parallax mapping
    {
       finalTexCoord = steepParallax(texCoord,viewDir);
    }
    else if(parallaxType == 3)//Parallax Occlusion Mapping
    {
       finalTexCoord = parallaxOcclusion(texCoord,viewDir);
    }
    return finalTexCoord;
}

void main()
{
    vec3 viewDir = normalize(tangentViewPos - tangentFragPos);
    vec2 texCoord = parallaxMapping(TexCoord,viewDir);
    if(texCoord.x > 1.0 || texCoord.x < 0.0 || texCoord.y > 1.0 || texCoord.y < 0.0)
        discard;

    vec3 color = vec3(texture(texture1,texCoord));
    vec3 ambient = color * vec3(0.1);

    vec3 normal = vec3(texture(normalTexture,texCoord));
    normal = normalize(normal * 2.0 - 1.0);

    
    vec3 lightDir = normalize(tangentLightPos - tangentFragPos);

    float diff = max(dot(lightDir,normal),0.0f);
    vec3 diffuse = color * diff;

    vec3 halfDir = normalize(viewDir + lightDir);
    float spec = pow(max(dot(halfDir,normal),0.0f),32.0);
    vec3 specular = vec3(1.0) * spec;

    FragColor = vec4(ambient + diffuse + specular,1.0f);
}