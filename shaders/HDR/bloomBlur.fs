#version 450 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

uniform bool horizontal;

void main()
{
    vec2 offset = 1.0 / textureSize(texture1,0);
    vec3 color = texture(texture1,TexCoord).rgb * weight[0];
     
    if(horizontal)
    {
        for(int i = 1;i < 5;i++)
        {
            color += texture(texture1,TexCoord + vec2(offset.x * i,0.0)).rgb * weight[i];
            color += texture(texture1,TexCoord - vec2(offset.x * i,0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1;i < 5;i++)
        {
            color += texture(texture1,TexCoord + vec2(0.0,offset.y * i)).rgb * weight[i];
            color += texture(texture1,TexCoord - vec2(0.0,offset.y * i)).rgb * weight[i];
        }
    }
    
    FragColor = vec4(color,1.0);
}