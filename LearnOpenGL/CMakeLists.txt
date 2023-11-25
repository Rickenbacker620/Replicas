cmake_minimum_required(VERSION 3.0.0)

project(LearnOpenGL VERSION 0.1.0)

SET(CMAKE_INSTALL_PREFIX $ENV{HOME}/.local)

include(FetchContent)

FetchContent_Declare(glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw"
    GIT_TAG "3.3.8" )

FetchContent_MakeAvailable(glfw)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_custom_target(
    format
    COMMAND ${PROJECT_SOURCE_DIR}/format.sh
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_subdirectory(vendor/glad)

add_subdirectory(lib)

add_executable(LearnOpenGL src/main.cpp)

target_link_libraries(LearnOpenGL
    PRIVATE
    LGL)

add_dependencies(LearnOpenGL format)

set_property(TARGET LearnOpenGL PROPERTY CXX_STANDARD 20)