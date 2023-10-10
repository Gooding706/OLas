#include <VBO.h>

VBO::VBO(size_t buffers )
{
    glGenBuffers(buffers, &ID);
}

unsigned int VBO::GetID()
{
    return ID;
}

void VBO::AssignData(OTypes::Vertex *Shape, size_t elements)
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(OTypes::Vertex) * elements, Shape, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OTypes::Vertex), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(OTypes::Vertex), (void *)(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    this->VerticesCount = elements;
}

size_t VBO::GetCount()
{
    return VerticesCount;
}