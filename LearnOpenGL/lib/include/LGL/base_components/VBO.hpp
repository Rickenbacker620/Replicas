#pragma once
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>
#include <string>
#include <string_view>

class VBO
{
  private:
    GLuint _vbo;

  public:
    VBO(float vertices[], size_t size);
    void bind();
    void unbind();
    ~VBO();
};
