#version 300 es

in vec3 coords;
in vec2 vertexColor;

out vec2 UV;
uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(coords,1.0);
    UV = vertexColor;
}
