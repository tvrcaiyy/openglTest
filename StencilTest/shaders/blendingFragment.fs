#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{    
    vec4 color = texture(texture1,TexCoords);
    FragColor = color;
}
