cmake_minimum_required (VERSION 3.5)

project (perlin-noise)

set (source_dir "${PROJECT_SOURCE_DIR}/src/")

file (GLOB source_files "${source_dir}/*.cpp")

add_executable (perlin-noise "${source_files}")
