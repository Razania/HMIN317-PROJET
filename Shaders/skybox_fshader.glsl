#version 330 core
#extension GL_NV_shadow_samplers_cube : enable

out vec4 fragColor;

uniform samplerCube skyboxTexture;

in vec3 texCoords;

void main(void)
{
    //gl_FragColor = vec4(0.5,0,0,1);

    fragColor = textureCube(skyboxTexture, texCoords);
}
