#include "LGL/base_components/shader.hpp"

#include <iostream>
#include <string_view>

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

std::pair<std::string, std::string> Shader::readSourceText(std::string_view vPath, std::string_view fPath)
{
    std::ifstream vertexfile(vPath.data());
    std::ifstream fragfile(fPath.data());
    std::string line;
    std::stringstream ss[2];

    while (getline(vertexfile, line))
    {
        ss[0] << line << '\n';
    }
    while (getline(fragfile, line))
    {
        ss[1] << line << '\n';
    }
    return {ss[0].str(), ss[1].str()};
}

Shader::Shader(std::string_view vPath, std::string_view fPath) : _shaderProgram(glCreateProgram())
{
    auto [vertexShaderSource, fragmentShaderSource] = readSourceText(vPath, fPath);
    auto vShader = compilerShader(GL_VERTEX_SHADER, vertexShaderSource);
    auto fShader = compilerShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    bindShader(vShader, fShader);
};

Shader::~Shader()
{
    // glDeleteProgram(this->_shaderProgram);
    std::cout << "deleted";
}