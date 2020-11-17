#version 150

uniform sampler2D texture;

in vec2 texCoords;

//! [0]
void main()
{
    gl_FragColor = texture2D(texture,texCoords);
}
//! [0]

