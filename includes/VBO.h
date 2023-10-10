#pragma once
#include <Types.h>
#include <iostream>
#include <array>
#include <glad.h>


class VBO
{
public:
    VBO(size_t buffers = 1);

    unsigned int GetID();

    void AssignData(OTypes::Vertex* Shape, size_t elements);

    size_t GetCount();
private:
    unsigned int ID = 0;
    size_t VerticesCount = 0;
};
