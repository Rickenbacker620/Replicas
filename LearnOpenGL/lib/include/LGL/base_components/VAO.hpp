#pragma once
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>
#include <string>
#include <string_view>

class VAO
{
  private:
    GLuint _vao;

  public:
    VAO();
    void setAttributePointer();
    ~VAO();
    void bind();
    void unbind();
    GLuint getVAO();
};
