#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

/** Compiles the shader source code and returns ID of that shader
 * @param shaderType the type of shader
 * @param shaderCode the source code of the shader as a string literal
 * @return ID returns the ID of the compiled shader
 */
unsigned int compileShader(unsigned int shaderType, std::string &shaderCode)
{
    printf("LOG: Compiling shader: %s\n", shaderType == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader");
    int result = GL_FALSE;
    int infoLogLength;
    unsigned int shaderID = glCreateShader(shaderType);

    // Compile Shader
    char const* vertexSourcePtr = shaderCode.c_str();
    glShaderSource(shaderID, 1, &vertexSourcePtr, NULL);
    glCompileShader(shaderID);

    // Check Shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength > 0)
    {
        std::vector<char> vertexShaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
        printf("%s\n", &vertexShaderErrorMessage[0]);
        return 0;
    }
    return shaderID;
}

/** Reads the file name given into a std::string
 * 
 * @param shaderFile filepath of the shader file
 * @return returns the source code of the shaderFile as a string
 */
std::string readShaderFile(const char* shaderFile)
{
    printf("LOG: Reading shader: %s\n", shaderFile);
    std::string shaderCode;
    std::ifstream shaderStream(shaderFile, std::ios::in);
    if (shaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
    }
    else
    {
        {
            printf("ERROR: Impossible to open %s\n", shaderFile);
            getchar();
            return "";
        }
    }
    return shaderCode;
}

unsigned int createShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile)
{
    std::string vertexShaderCode = readShaderFile(vertexShaderFile);
    unsigned int vertexShaderID = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
    
    std::string fragmentShaderCode = readShaderFile(fragmentShaderFile);
    unsigned int fragmentShaderID = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    // Link program
    printf("LOG: Linking program\n");
    unsigned int programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    int result = GL_FALSE;
    int infoLogLength;
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