#version 330 core
precision mediump float;

uniform sampler2D texUnit;
uniform vec3 lightPos;
uniform vec4 lightDir;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 outputF;

void main()
{

    vec4 test = texture2D(texUnit, TexCoord);
    //test = vec4(test.x, test.y, test.z, 1.0f);

    float ambientStrength = 0.1f;
    vec3 LightColor = vec3(0.5f, 0.5f, 1.0f);
    vec3 spotlightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambient = ambientStrength * LightColor * test.xyz;

    vec3 surfaceToLight = normalize(lightPos.xyz - FragPos);
    vec3 pointat = vec3(lightDir.x, lightDir.y, lightDir.z);
    vec3 coneDirection = lightPos - pointat;
    //vec3 rayDirection = -surfaceToLight;
    float lightToSurfaceAngle = degrees(acos(dot(surfaceToLight, normalize(coneDirection))));
    float attention = 1.0f;
    //float distanceToLight = length(lightPos.xyz - FragPos);
    //attention = 1.0 / (1.0 + 0.001 * pow(distanceToLight, 2));
    if(lightToSurfaceAngle > lightDir.w) {
      if(lightToSurfaceAngle - lightDir.w < 6.0f) {
        attention = (1.0/6.0) * -(lightToSurfaceAngle - lightDir.w) + 1.0f;
        if (attention < 0)
          attention = 0;
        //attention = 3.0;
      }
      else {
        attention = 0.0f;
      }
    }

    vec3 norm = normalize(Normal);
    float diffuseCo = max(0.0, dot(norm, surfaceToLight));
    vec3 objColor = vec3(test.x, test.y, test.z);
    vec3 diffuse = diffuseCo * objColor * spotlightColor;

    //vec3 lightDir = normalize(lightPos - FragPos); //lightPos - FragPos);
    //float diff = dot(norm, lightDir);
    //vec3 diffuse = diff * spotlightColor;

    objColor = vec3(test.x, test.y, test.z);
    vec3 result = ambient + attention * diffuse; //((ambient + diffuse) * objColor);

    vec4 outputc = vec4(result, test.w);
    if (outputc.w < 0.5)
      discard;

    outputF = outputc;
}
