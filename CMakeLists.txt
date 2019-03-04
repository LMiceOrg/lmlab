cmake_minimum_required(VERSION 2.8)

project(LMLab)

message(STATUS "Current generator starting  -G \"${CMAKE_GENERATOR}\" \"${CMAKE_SOURCE_DIR}\"")

message(STATUS "os: ${CMAKE_SYSTEM_NAME} compiler:${CMAKE_CXX_COMPILER_ID}")


# os -- compiler environment setting
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

    if (MSVC)
        # unicode
        add_definitions(-DUNICODE -D_UNICODE)

        # c/cpp standard
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14")
        set(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS_RELEASE} /std:c90")

    endif(MSVC)

endif()

# Document
add_subdirectory(doc)

# Execution manager
add_subdirectory(em)

# LMice Runtime Environment
add_subdirectory(lmrte)

# LMice Script
add_subdirectory(lmscript)

# LMice Deamon
add_subdirectory(lmiced)

