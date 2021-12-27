#version 330


out vec4 FragColor;

uniform float xColor; 

void main()
{
    FragColor = vec4(xColor, 0.5f, 0.31f, 1.0f);
}