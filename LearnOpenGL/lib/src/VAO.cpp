#include "LGL/base_components/VAO.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &this->_vao);
    this->bind();
}

void VAO::setAttributePointer()
{
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
}

void VAO::bind()
{
    glBindVertexArray(this->_vao);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

GLuint VAO::getVAO()
{
    return this->_vao;
}

VAO::~VAO()
{
    glDeleteShader(this->_vao);
}