project(LGL)

add_library(LGL STATIC src/init.cpp src/shader.cpp src/VAO.cpp src/VBO.cpp src/EBO.cpp)

target_link_libraries(LGL PUBLIC glad glfw)

target_include_directories(LGL PUBLIC include)
