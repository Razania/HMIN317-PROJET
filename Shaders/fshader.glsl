#version 330 core
#extension GL_EXT_texture_array : enable

out vec4 fragColor;

uniform sampler2DArray textureList;

in vec2 texCoords;
in vec4 v_normal;
in vec4 FragPos;
flat in int v_texlayer;

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

    float constant;
    float linear;
    float quadratic;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

const int MAX_DIRECTIONAL_LIGHTS = 10;
uniform int nbOfDirectionalLights;
uniform DirectionalLight directionalLights[MAX_DIRECTIONAL_LIGHTS];

const int MAX_POINT_LIGHTS = 100;
uniform int nbOfPointLights;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

const int MAX_SPOT_LIGHTS = 100;
uniform int nbOfSpotLights;
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

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));
    // combine results
    vec3 ambient  = light.ambient;
    vec3 diffuse  = light.diffuse  * diff;
    vec3 specular = light.specular * spec;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);

    vec3 ambient = light.ambient;
    vec3 diffuse = light.diffuse * diff;
    vec3 specular = light.specular * spec;

    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    ambient  *= intensity;
    diffuse  *= intensity;
    specular *= intensity;

    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient  *= attenuation;
    diffuse   *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

//! [0]
void main()
{
    vec3 norm = normalize(vec3(v_normal));
    vec3 viewDir = normalize(viewPos - vec3(FragPos));

    vec3 result = vec3(0,0,0);

    for(int i = 0; i < nbOfDirectionalLights; i++)
        result += CalcDirLight(directionalLights[i], norm, viewDir);

    for(int i = 0; i < nbOfPointLights; i++)
        result += CalcPointLight(pointLights[i], norm, vec3(FragPos), viewDir);

    for(int i = 0; i < nbOfSpotLights; i++){
        result += CalcSpotLight(spotLights[i], norm, vec3(FragPos), viewDir);
    }

    fragColor = vec4(result, 1) * texture2DArray(textureList, vec3(texCoords, v_texlayer));
}
//! [0]

