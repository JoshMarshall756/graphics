#ifndef COMMON_HPP
#define COMMON_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// buildTransformMatrix.cpp
glm::mat4 buildTransformationMatrix();

// generateRandomColor.cpp
float generateRandomColor();

// loadShader.cpp
unsigned int compileShader(unsigned int shaderType, std::string &shaderCode);
std::string readShaderFile(const char* shaderFile);
unsigned int createShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile);

// loadTexture.cpp
unsigned int loadBMP(const char* texturePath);

#endif