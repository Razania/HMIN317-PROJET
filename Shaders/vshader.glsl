#version 150

uniform mat4 mvp_matrix;

in vec4 a_position;
in vec2 a_texcoord;

out vec2 texCoords;

//! [0]
void main()
{
        // Calculate vertex position in screen space
        gl_Position = mvp_matrix * a_position;

        texCoords = a_texcoord;
}
//! [0]
