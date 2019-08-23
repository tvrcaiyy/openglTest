#version 450 core

in vec3 outColor;
in vec2 outTexCrood;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;
void main()
{
    FragColor = mix(texture(texture1,outTexCrood),texture(texture2,vec2(1-outTexCrood.x,outTexCrood.y)),mixValue);// * vec4(outColor,1.0f);
}