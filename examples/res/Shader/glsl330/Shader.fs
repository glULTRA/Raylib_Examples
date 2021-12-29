#version 330


out vec4 FragColor;

in vec4 fragColor;
in vec2 fragTexCoord;

uniform sampler2D texture0;
uniform float xColor; 

void main()
{
    FragColor = vec4(xColor, 0.5f, 1.0f, 1.0f);
    //FragColor = texture(texture0, fragTexCoord) * vec4(fragColor.x * xColor, fragColor.y, fragColor.z, fragColor.w);
}