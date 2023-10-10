#include <EBO.h>

unsigned int EBO::GetID()
{
    return ID;
}
EBO::EBO(size_t buffers)
{
    glGenBuffers(buffers, &ID);
}

size_t EBO::GetCount()
{
    return IndicesCount;
}

void EBO::AssignData(unsigned int *Indices, size_t Elements)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Elements, Indices, GL_STATIC_DRAW);
    this->IndicesCount = Elements;
}