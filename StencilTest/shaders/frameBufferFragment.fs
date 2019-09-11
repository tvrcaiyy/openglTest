#version 450 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

float offset = 1.0/300.0;
//��
//float kernel[9] = float[](
//        -1, -1, -1,
//        -1,  9, -1,
//        -1, -1, -1
//    );
//ģ��
//float kernel[9] = float[](
//    1.0 / 16, 2.0 / 16, 1.0 / 16,
//    2.0 / 16, 4.0 / 16, 2.0 / 16,
//    1.0 / 16, 2.0 / 16, 1.0 / 16  
//);
//��Ե���
float kernel[9] = float[](
        1,  1, 1,
        1, -8, 1,
        1,  1, 1
    );
vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // ����
        vec2( 0.0f,    offset), // ����
        vec2( offset,  offset), // ����
        vec2(-offset,  0.0f),   // ��
        vec2( 0.0f,    0.0f),   // ��
        vec2( offset,  0.0f),   // ��
        vec2(-offset, -offset), // ����
        vec2( 0.0f,   -offset), // ����
        vec2( offset, -offset)  // ����
    );
void main()
{   
    //����
    //FragColor = vec4(vec3(1.0 - texture(screenTexture,TexCoords)),1.0f);
    //�Ҷ�
    //vec3 color = texture(screenTexture,TexCoords).rgb;
    //float average = color.r * 0.2125 + color.g * 0.7152 + color.b + 0.0722;
    //FragColor = vec4(average,average,average,1.0f);

    //�˾��Ч��
    vec3 sampleTex[9];
    for(int i = 0;i < 9;i++)
        sampleTex[i] = vec3(texture(screenTexture,TexCoords + offsets[i]));
    
    vec3 col = vec3(0.0);
    for(int i = 0;i < 9;i++)
        col += sampleTex[i] * kernel[i];
    
    FragColor = vec4(col, 1.0);
}
