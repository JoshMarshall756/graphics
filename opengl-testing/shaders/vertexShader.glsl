#version 330 core

layout (location = 0) in vec4 vertexPosition_modelSpace;
layout (location = 1) in vec2 vertexUV;

// Values that stay constant for the whole mesh
uniform mat4 MVP;

// Output data. will be interpolated for each fragment
out vec2 UV;

void main()
{
    gl_Position = MVP * vec4(vertexPosition_modelSpace);
    UV = vertexUV;
}