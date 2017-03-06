#version 300 es

in vec3 position;
in vec2 texCoord;
in vec3 normal;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 MVP;
uniform mat4 Model;

void main() {
    gl_Position = MVP * Model * vec4(position, 1.0f);
    TexCoord = texCoord;
    vec4 stupidthing =  Model * vec4(position.x, position.y, position.z, 1.0f);
    FragPos = vec3(stupidthing.x, stupidthing.y, stupidthing.z);
    Normal = normal;
}
