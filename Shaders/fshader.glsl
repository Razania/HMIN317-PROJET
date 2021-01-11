#version 330 core

uniform sampler2DArray textureList;

in vec2 texCoords;
in vec4 v_normal;
in vec4 FragPos;
flat in uint v_texlayer;

//Lights
uniform vec3 viewPos;

struct DirectionalLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight{
    vec3 direction;
    vec3 position;
    float cutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

const int MAX_DIRECTIONAL_LIGHTS = 100;
uniform int nbOfDirectionalLights;
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];

const int MAX_POINT_LIGHTS = 1000;
uniform int nbOfPointLights;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

const int MAX_SPOT_LIGHTS = 1000;
uniform int nbOfSpotLight;
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    // combine results
    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * diff;
    vec3 specular = light.specular * spec;
    return (ambient + diffuse + specular);
}

//! [0]
void main()
{
    vec3 norm = normalize(vec3(v_normal));
    vec3 viewDir = normalize(viewPos - vec3(FragPos));

    vec3 result = vec3(0,0,0);

    for(int i = 0; i < MAX_DIRECTIONAL_LIGHTS; i++)
            result += CalcDirLight(directionalLights[i], norm, viewDir);

    gl_FragColor = vec4(result, 1) * texture2DArray(textureList, vec3(texCoords, v_texlayer));
}
//! [0]

