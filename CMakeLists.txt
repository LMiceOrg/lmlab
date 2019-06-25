cmake_minimum_required(VERSION 3.1.0)

project(LMLab)

message(STATUS "Current generator starting  -G \"${CMAKE_GENERATOR}\" \"${CMAKE_SOURCE_DIR}\" Built type ${CMAKE_BUILD_TYPE}")

message(STATUS "os: ${CMAKE_SYSTEM_NAME} compiler:${CMAKE_CXX_COMPILER_ID}")


# os -- compiler environment setting
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

    if (MSVC)
        # unicode
        add_definitions(-DUNICODE -D_UNICODE)

        # c/cpp standard
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14")
        set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} /std:c90")

    endif(MSVC)

    if(MINGW)
        find_package(PkgConfig REQUIRED)

        add_definitions("-DUNICODE -D_UNICODE")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -mtune=native")
        set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -std=c90 -march=native -mtune=native")

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}   -fexec-charset=gb18030")
        set(CMAKE_C_FLAGS "${CMAK_C_FLAGS}  -fexec-charset=gb18030")
    endif()
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # unicode support
    add_definitions("-DUNICODE -D_UNICODE")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native -mtune=native")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -std=c90 -march=native -mtune=native")
    # 常年表达式递归计算限制
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconstexpr-backtrace-limit=0")

endif()


# EAL library
FIND_PATH(eal_header lmice_trace.h
    PATHS ../lmalpha/eal ../alpha/eal)
LIST(APPEND eal_SRCS
    #${eal_header}/lmice_ring.c
    ${eal_header}/lmice_trace.c
    ${eal_header}/lmice_eal_shm.c
    ${eal_header}/lmice_eal_hash.c
    #${eal_header}/lmice_eal_spinlock.c
    #${eal_header}/lmice_eal_malloc.c
    #${eal_header}/lmice_eal_event.c
    ${eal_header}/lmice_eal_time.c
    #${eal_header}/lmice_core.c
    #${eal_header}/lmice_eal_aio.c
    ${eal_header}/lmice_eal_thread.c
    #${eal_header}/lmice_bloomfilter.c
    ${eal_header}/lmice_eal_common.h
    )

#Shared EAL Library
#ADD_LIBRARY(eal SHARED ${EAL_SRCS})

#Static EAL Library
ADD_LIBRARY(eal_static STATIC ${eal_SRCS})
SET_TARGET_PROPERTIES(eal_static PROPERTIES OUTPUT_NAME "eal")
SET_TARGET_PROPERTIES(eal_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
#SET_TARGET_PROPERTIES(eal_static PROPERTIES VERSION 1.2 SOVERSION 1)
INCLUDE_DIRECTORIES(${eal_header})


# Document
add_subdirectory(doc)

# Execution manager
add_subdirectory(em)

# LMice Runtime Environment
add_subdirectory(lmrte)

# LMice Script
#add_subdirectory(lmscript)

# LMice Deamon
add_subdirectory(lmiced)

