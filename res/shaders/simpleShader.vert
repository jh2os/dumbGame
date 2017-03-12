#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 thing;
layout (location = 4) in vec3 voffset;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

//uniform mat4 MVP;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() {
    vec4 instancePos = vec4(position + voffset, 1.0f);
    gl_Position = Projection * View * Model * instancePos;
    TexCoord = texCoord;
    vec4 stupidthing =  Model * instancePos;
    FragPos = vec3(stupidthing.x, stupidthing.y, stupidthing.z);
    Normal = normal;
}
