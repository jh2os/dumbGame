#version 300 es
precision mediump float;

out vec3 FragColor;

void main() {
    
    FragColor = vec3(1,1,1)  * texture(myTextureSampler, UV).rgb;;
}
