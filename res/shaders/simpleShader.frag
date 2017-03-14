#version 330 core
precision mediump float;

uniform sampler2D texUnit;
uniform vec3 lightPos;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 outputF;

void main()
{

    vec4 test = texture2D(texUnit, TexCoord);
    //test = vec4(test.x, test.y, test.z, 1.0f);

    float ambientStrength = 0.5f;
    vec3 LightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambient = ambientStrength * LightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos); //lightPos - FragPos);
    float diff = dot(norm, lightDir);
    vec3 diffuse = diff * LightColor;


    vec3 objColor = vec3(test.x, test.y, test.z);
    vec3 result = (ambient + diffuse) * objColor;

    vec4 outputc = vec4(result, test.w);
    if (outputc.w < 0.5)
      discard;

    outputF = outputc;
}
