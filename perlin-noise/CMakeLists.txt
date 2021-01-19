cmake_minimum_required (VERSION 3.11...3.18)
project (perlin-noise VERSION 1.0.0 LANGUAGES C CXX)

include(cmake/PreventInSourceBuilds.cmake)
add_library(StandardProjectSettings INTERFACE)
assureOutOfSourceBuilds()

include(cmake/CompilerWarnings.cmake)
add_library(ProjectWarnings INTERFACE)
setCompilerWarnings(ProjectWarnings)

add_executable(perlin_noise src/application.cpp)
target_link_libraries(perlin_noise ProjectWarnings StandardProjectSettings)
