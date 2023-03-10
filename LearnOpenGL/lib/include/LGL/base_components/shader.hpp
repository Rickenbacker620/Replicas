#pragma once
// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>
#include <string>
#include <string_view>

class Shader
{
  private:
    const GLuint _shaderProgram;

  public:
    Shader(std::string vPath, std::string fPath);
    ~Shader();
    GLuint getProgram();
    void bindShader(GLuint vertexShader, GLuint fragmentShader);
    GLuint compilerShader(GLenum sType, std::string_view sSource);
};

GLuint Shader::getProgram()
{
    return this->_shaderProgram;
};

GLuint Shader::compilerShader(GLenum sType, std::string_view sSource)
{
    const GLuint shader = glCreateShader(sType);

    const char *sSourceData = sSource.data();

    glShaderSource(shader, 1, &sSourceData, NULL);

    glCompileShader(shader);

    int success;
    char infoLog[512];

    const char *errorMsg = nullptr;

    switch (sType)
    {
    case GL_VERTEX_SHADER: errorMsg = "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"; break;
    case GL_FRAGMENT_SHADER: errorMsg = "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"; break;
    default: break;
    }

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << errorMsg << infoLog << std::endl;
    }
    return shader;
};

void Shader::bindShader(GLuint vertexShader, GLuint fragmentShader)
{
    auto &program = this->_shaderProgram;
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    // check for linking errors
    int success;
    char infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
};

Shader::Shader(std::string vPath, std::string fPath) : _shaderProgram(glCreateProgram())
{
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";

    auto vShader = compilerShader(GL_VERTEX_SHADER, vertexShaderSource);
    auto fShader = compilerShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    bindShader(vShader, fShader);
};

Shader::~Shader()
{
    // glDeleteProgram(this->_shaderProgram);
    std::cout << "deleted";
}
