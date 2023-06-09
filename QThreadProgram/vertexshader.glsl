#version 330 core

layout(location = 0) in vec3 vertexPos;
uniform mat4 transformMatrix;

void main()
{
   gl_Position = mvp * vec4(vertexPos, 1);
}