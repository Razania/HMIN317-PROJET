#version 330 core

uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat4 p_matrix;

in vec4 a_position;
in vec4 a_normal;
in vec2 a_texcoord;
in int a_texlayer;

out vec2 texCoords;
out vec4 v_normal;
out vec4 FragPos;
flat out int v_texlayer;

//! [0]
void main()
{
        // Calculate vertex position in screen space
        mat4 mvp_matrix = p_matrix * v_matrix * m_matrix;
        gl_Position = mvp_matrix * a_position;

        texCoords = a_texcoord;
        v_normal = a_normal;
        FragPos = m_matrix * a_position;
        v_texlayer = a_texlayer;
}
//! [0]
