cmake_minimum_required(VERSION 2.8)

project(lmrte)
set(EXECUTABLE_OUTPUT_PATH  "${CMAKE_BINARY_DIR}")
set(LIBRARY_OUTPUT_PATH  "${CMAKE_BINARY_DIR}")

LIST(APPEND lmrte_sources
    main.cpp)

add_executable(${PROJECT_NAME} ${lmrte_sources})
