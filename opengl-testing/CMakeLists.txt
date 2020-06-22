cmake_minimum_required(VERSION 3.5)

project(openglTesting VERSION 0.1)
include(cmake/StandardProjectSettings.cmake)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)
include(cmake/CompilerWarnings.cmake)
set_compiler_warnings(project_warnings)

configure_file(config/openglTestingConfig.h.in openglTestingConfig.h)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED STATIC)
find_package(glm REQUIRED)

set(source_dir "${PROJECT_SOURCE_DIR}/src/")

file(GLOB source_files "${source_dir}/*.cpp" "${source_dir}/common/*.cpp")

add_executable(openglTesting "${source_files}")

target_include_directories(openglTesting PUBLIC headers "${PROJECT_BINARY_DIR}")

target_link_libraries(openglTesting glfw OpenGL::GL ${GLEW_LIBRARY} glm project_warnings)