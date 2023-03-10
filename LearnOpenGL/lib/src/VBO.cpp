#include "LGL/base_components/VBO.hpp"

VBO::VBO(float vertices[], size_t size)
{
    glGenBuffers(1, &this->_vbo);
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
}
void VBO::unbind()
{

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VBO::~VBO()
{

    glDeleteShader(this->_vbo);
}