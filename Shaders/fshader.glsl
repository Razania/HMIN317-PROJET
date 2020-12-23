#version 410 core
uniform sampler2DArray textureList;
uniform sampler2D texture;

in vec2 texCoords;
in vec4 v_normal;
in vec4 FragPos;
flat in int a_texLayer;

//! [0]
void main()
{
    vec3 lightPos = vec3(0,200,0);
    vec3 lightColor = vec3(1,1,1);

    vec3 norm = normalize(vec3(v_normal));
    vec3 lightDir = normalize(lightPos - vec3(FragPos));

    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = ambient + diffuse;


    gl_FragColor = vec4(result, 1) * texture2D(texture,texCoords);
    //gl_FragColor = /*vec4(result, 1) **/ texture2DArray(textureList,vec3(texCoords,0));
}
//! [0]

