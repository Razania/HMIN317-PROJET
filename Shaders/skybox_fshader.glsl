#version 330 core

uniform samplerCube skyboxTexture;

in vec3 texCoords;

void main(void)
{
    //gl_FragColor = vec4(0.5,0,0,1);

    gl_FragColor = textureCube(skyboxTexture, texCoords);
}
