#include<VAO.h>

VAO::VAO(size_t buffers)
{
    glGenVertexArrays(buffers, &ID);
    glBindVertexArray(ID);
}

unsigned int VAO::GetID()
{
    return ID;
}