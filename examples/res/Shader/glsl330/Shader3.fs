#version 330 

out vec4 finalColor;

in vec2 fragTexCoord;
in vec3 fragColor;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

void main(){
    vec4 texelColor = texture(texture0, fragTexCoord);

    float gray = dot(texelColor.rgb, vec3(0.299, 0.587, 0.114));
    
    finalColor = vec4(gray ,gray ,gray ,texelColor);
}