cmake_minimum_required(VERSION 3.15)

set(DEBUG_VERSION "DebugMode")
set(RELEASE_VERSION "ReleaseMode")
set(COMPILE_MODE ${RELEASE_VERSION})
set(PROJECT_NAME "OpenMPDemo")

# debug mode (project name + compile time)
if(${COMPILE_MODE} MATCHES ${DEBUG_VERSION})
    set(USE_RELEASE_MODE 0)
    set(CMAKE_BUILD_TYPE "Debug")
    string(TIMESTAMP COMPILE_TIME %y%m%d_%H%M%S)
# release mode (project name + version)
else()
    set(USE_RELEASE_MODE 1)
    set(CMAKE_BUILD_TYPE "Release")
    set(VERSION_MAJOR 0)
    set(VERSION_MINOR 0)
    set(VERSION_PATCH 0)
    set(VERSION_TWEAK 1)
endif()

project(${PROJECT_NAME})

configure_file(
    "include/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

include_directories(
    include
    "${PROJECT_BINARY_DIR}"
)

find_package(OpenMP REQUIRED)
if(OpenMP_CXX_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    message(FATAL_ERROR "OpenMP not found")
endif()

aux_source_directory(src SRC_DIR)

add_executable(${PROJECT_NAME} ${SRC_DIR})

if(ANDROID)
target_link_libraries(${PROJECT_NAME} -fopenmp -static-openmp)
else()
target_link_libraries(${PROJECT_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
