#version 450 core

in vec3 ourColor;
in vec2 ourTexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;

float near = 0.1f;
float far = 100.0f;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0f - 1.0f;//back to ndc
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    FragColor = mix(texture(texture1,ourTexCoord),texture(texture2,ourTexCoord),mixValue);    
    //float depth = LinearizeDepth(gl_FragCoord.z) / far;
    //FragColor = vec4(vec3(depth),1.0f);
}