cmake_minimum_required(VERSION 2.8)


project(em)
set(EXECUTABLE_OUTPUT_PATH  "${CMAKE_BINARY_DIR}")
set(LIBRARY_OUTPUT_PATH  "${CMAKE_BINARY_DIR}")

set(em_src em.cpp em1.c)

add_executable(${PROJECT_NAME} ${em_src})
