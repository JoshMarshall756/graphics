cmake_minimum_required(VERSION 3.5)

project(openglTesting VERSION 0.1)
include(cmake/PreventInSourceBuilds.cmake)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED STATIC)
find_package(glm REQUIRED)

configure_file(config/openglTestingConfig.h.in openglTestingConfig.h)

# Link this 'library' to include my standard project settings
include(cmake/StandardProjectSettings.cmake)
add_library(standard_project_settings INTERFACE)


# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_compiler_warnings(project_warnings)

# This library is the main library
set(source_dir "${PROJECT_SOURCE_DIR}/src/")

add_executable(openglTesting 
                src/application.cpp
                src/common/buildTransformMatrix.cpp
                src/common/controls.cpp
                src/common/generateRandomColor.cpp
                src/common/loadObj.cpp
                src/common/loadShader.cpp
                src/common/loadTexture.cpp)

target_include_directories(openglTesting PUBLIC headers "${PROJECT_BINARY_DIR}")
target_link_libraries(openglTesting PUBLIC glfw OpenGL::GL ${GLEW_LIBRARY} glm project_warnings standard_project_settings)