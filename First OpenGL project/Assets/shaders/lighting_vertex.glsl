#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D texture1;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * TexCoord;

    vec3 result = ambient * objectColor;
   //FragColor = vec4(result, 1.0);
    FragColor = texture(texture1, TexCoord);
}  
