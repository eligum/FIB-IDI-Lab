#version 330 core

in vec3 vertex;
in vec3 color;

uniform mat4 u_TG;
uniform mat4 u_Proj;
uniform mat4 u_View;

out vec3 fcolor;

void main()
{
    fcolor = color;
    gl_Position = u_Proj * u_View * u_TG * vec4 (vertex, 1.0);
}
