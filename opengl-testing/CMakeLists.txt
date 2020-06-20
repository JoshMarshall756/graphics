cmake_minimum_required (VERSION 3.5)

project (openglTesting)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED STATIC)
find_package(glm REQUIRED)

set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*.cpp" "${source_dir}/common/*.cpp")

add_executable (openglTesting "${source_files}")

target_include_directories(openglTesting PRIVATE headers)

target_link_libraries(openglTesting glfw OpenGL::GL ${GLEW_LIBRARY} glm)

target_compile_options(openglTesting PRIVATE -Werror -Wall -Wextra)