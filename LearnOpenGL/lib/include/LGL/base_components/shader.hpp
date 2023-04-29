#pragma once
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>

class Shader
{
  private:
    const GLuint _shaderProgram;

  public:
    Shader(std::string_view vPath, std::string_view fPath);
    ~Shader();
    GLuint getProgram();
    void bindShader(GLuint vertexShader, GLuint fragmentShader);
    std::pair<std::string, std::string> readSourceText(std::string_view vPath, std::string_view fPath);
    GLuint compilerShader(GLenum sType, std::string_view sSource);
};
