#version 330 core

in vec3 a_position;

out vec3 texCoords;

uniform mat4 p_matrix;
uniform mat4 v_matrix;

void main()
{
    texCoords = a_position;
    vec4 pos =  p_matrix * v_matrix * vec4(a_position, 1.0);
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
}
