#version 330 core

layout (location = 0) in vec4 vertexPosition_modelSpace;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(vertexPosition_modelSpace);
}