cmake_minimum_required (VERSION 3.5)

project (opengl-testing)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED STATIC)

set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*.cpp")

add_executable (opengl-testing "${source_files}")

target_link_libraries(opengl-testing glfw OpenGL::GL ${GLEW_LIBRARY})