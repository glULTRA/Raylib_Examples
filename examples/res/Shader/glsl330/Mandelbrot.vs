#version 330

in vec3 vertexPosition;
out vec2 coord;

// Input uniform values
uniform mat4 mvp;

out vec4 fragColor;

void main() {
    gl_Position = mvp * vec4(vertexPosition, 1.0);
    coord.x = vertexPosition.x;
    coord.y = vertexPosition.y;
}