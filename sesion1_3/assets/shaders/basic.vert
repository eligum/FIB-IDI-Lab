#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

//uniform float uFactor;
uniform mat4 uTG;

out vec4 vertexColor;

void main()
{
    gl_Position = uTG * vec4(aPos, 1.0);
    vertexColor = vec4(aColor, 1.0);
}
