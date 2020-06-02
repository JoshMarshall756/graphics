// Load and compile shaders from a file

#pragma once

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

unsigned int createShader(const char* vertexShaderFile, const char* fragmentShaderFile)
{
    // Create shaders
    unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Open and read from vertex file
    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vertexShaderFile, std::ios::in);
    if(vertexShaderStream.is_open())
    {
        std::stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		vertexShaderCode = sstr.str();
		vertexShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s", vertexShaderFile);
        getchar();
        return 0;
    }
    
    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(fragmentShaderFile, std::ios::in);
    if(fragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << fragmentShaderStream.rdbuf();
        fragmentShaderCode = sstr.str();
        fragmentShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s", fragmentShaderFile);
        getchar();
        return 0;
    }

    int result = GL_FALSE;
    int infoLogLength;

    // Compile Vertex Shader
    printf("Compiling shader: %s\n", vertexShaderFile);
    char const* vertexSourcePtr = vertexShaderCode.c_str();
    glShaderSource(vertexShaderID, 1, &vertexSourcePtr, NULL);
    glCompileShader(vertexShaderID);

    // Check vertex Shader
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> vertexShaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        printf("%s\n", &vertexShaderErrorMessage[0]);
    }

    infoLogLength = 0;

    // Compile Fragment Shader
    printf("Compiling shader: %s\n", fragmentShaderFile);
    char const* fragmentSourcePtr = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &fragmentSourcePtr, NULL);
    glCompileShader(fragmentShaderID);

    // Check fragment shader
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> fragmentShaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
        printf("%s\n", &fragmentShaderErrorMessage[0]);
    }

    infoLogLength = 0;

    // Link program
    printf("Linking program\n");
    unsigned int programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    // Check program
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> programErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
        printf("%s\n", &programErrorMessage[0]);
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}
