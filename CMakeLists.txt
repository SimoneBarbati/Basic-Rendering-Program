cmake_minimum_required(VERSION 3.28.3)

project(BRP VERSION 0.0.1)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(GLAD_SRC_DIR "/usr/src/glad")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(GLAD_INCLUDE_DIR "/usr/include/glad")

file(GLOB_RECURSE PROJECT_SOURCE "${SRC_DIR}/*.cpp")
file(GLOB GLAD_SOURCE "${GLAD_SRC_DIR}/glad.c")

include_directories(${INCLUDE_DIR} ${GLAD_INCLUDE_DIR})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

link_libraries(glfw OpenGL::GL)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE} ${GLAD_SOURCE})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build Type" FORCE)
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG>)

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")