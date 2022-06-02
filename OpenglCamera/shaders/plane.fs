#version 330 core

out vec4 FragColor;
uniform vec3 color;
in vec3 FragPos; 
in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
    FragColor = vec4(color,0.01);
   // FragColor = texture(texture1,TexCoord);
}