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

// loadOBJ.cpp
/**
 *  Load a 3D mesh from a file
 * 
 * @param path relative path to file
 * @param outVertices an std::vector<glm::vec3> for the read vertices to be loaded into
 * @param outUvs an std::vector<glm::vec2> for the read UV mappings to be loaded into
 * @param outNormals and std::vector<glm::vec3> fot the read normals to be loaded into
 * @return returns false if something went wrong 
 */
bool loadObj(
    const char* path, 
    std::vector<glm::vec3> &outVertices,
    std::vector<glm::vec2> &outUvs,
    std::vector<glm::vec3> &outNormals
    );

#endif