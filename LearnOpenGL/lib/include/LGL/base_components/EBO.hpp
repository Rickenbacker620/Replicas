#pragma once
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>
#include <string>
#include <string_view>

class EBO
{
  private:
    GLuint _ebo;

  public:
    EBO(uint32_t indices[], size_t size);
    void bind();
    ~EBO();
};
