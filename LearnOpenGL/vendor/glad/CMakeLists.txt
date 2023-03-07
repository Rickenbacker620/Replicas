project(glad)

add_library(${PROJECT_NAME} SHARED src/gl.c)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(glad PROPERTIES PUBLIC_HEADER ${PROJECT_SOURCE_DIR}/include/glad/gl.h)

install(TARGETS glad
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/glad)