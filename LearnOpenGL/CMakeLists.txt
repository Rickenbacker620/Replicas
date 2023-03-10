cmake_minimum_required(VERSION 3.0.0)

project(LearnOpenGL VERSION 0.1.0)

SET(CMAKE_INSTALL_PREFIX $ENV{HOME}/.local)

find_package(glfw3 3.3 REQUIRED)

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