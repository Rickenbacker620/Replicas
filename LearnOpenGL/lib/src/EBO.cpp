#include "LGL/base_components/EBO.hpp"

EBO::EBO(uint32_t indices[], size_t size)
{
    glGenBuffers(1, &this->_ebo);
    this->bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
}

EBO::~EBO()
{
    glDeleteShader(this->_ebo);
}