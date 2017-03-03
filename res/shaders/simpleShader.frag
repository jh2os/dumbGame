#version 300 es
precision mediump float;


uniform sampler2D texUnit;
in vec2 TexCoord;
out vec4 outputF;

void main()
{
    vec4 test = texture(texUnit, TexCoord);
    if (test.a < 0.5)
      discard;
    outputF = test; 
}
