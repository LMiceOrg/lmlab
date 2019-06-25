cmake_minimum_required(VERSION 2.8)

project(lmrte)
set(EXECUTABLE_OUTPUT_PATH  "${CMAKE_BINARY_DIR}")
set(LIBRARY_OUTPUT_PATH  "${CMAKE_BINARY_DIR}")

LIST(APPEND lmrte_sources
    main.cpp
    rte_client.cpp
    lmrte.h
    lmrte.hpp)

add_executable(${PROJECT_NAME}.exe ${lmrte_sources})
add_dependencies(${PROJECT_NAME}.exe eal_static)
target_link_libraries(${PROJECT_NAME}.exe eal_static)
add_definitions(-DLMRTE_PROJECT)


# Unit test
list(APPEND lmrte_tests
    ../tests/rte_hash.cpp)

add_executable(${PROJECT_NAME}_test ${lmrte_tests})
add_dependencies(${PROJECT_NAME}_test eal_static)
target_link_libraries(${PROJECT_NAME}_test eal_static)
target_include_directories(${PROJECT_NAME}_test PUBLIC .)
