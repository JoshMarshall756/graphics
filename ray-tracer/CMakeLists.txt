cmake_minimum_required (VERSION 3.5)

project (ray-tracer)

set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*.cpp")

add_executable (ray-tracer "${source_files}")
