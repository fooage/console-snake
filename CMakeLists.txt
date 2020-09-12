cmake_minimum_required(VERSION 2.8)

project(snake)

aux_source_directory(./src SrcFiles)

include_directories(&{PROJECT_SOURCE_DIR}/inc)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(snake ${SrcFiles})