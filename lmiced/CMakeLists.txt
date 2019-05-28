cmake_minimum_required(VERSION 2.8)

project(lmiced)
set(EXECUTABLE_OUTPUT_PATH  "${CMAKE_BINARY_DIR}")
set(LIBRARY_OUTPUT_PATH  "${CMAKE_BINARY_DIR}")

LIST(APPEND lmiced_sources
    lmiced.cpp
    lmiced.h

    board.h
    board.cpp
    resource.h
    resource.cpp

    lmice_eal_list.h
    lmice_eal_list.c
   )

add_executable(${PROJECT_NAME} ${lmiced_sources})
add_dependencies(${PROJECT_NAME} eal_static)
target_link_libraries(${PROJECT_NAME} eal_static)
target_include_directories(${PROJECT_NAME} PUBLIC ../lmrte)
#添加管理员权限
#/SUBSYSTEM:WINDOWS
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS
    "/MANIFESTUAC:\"level='requireAdministrator'
    uiAccess='false'\" ")
