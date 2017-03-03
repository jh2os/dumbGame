#version 300 es

in vec3 position;
in vec2 texCoord;
out vec2 TexCoord;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(position, 1.0);
    TexCoord = texCoord;
}

