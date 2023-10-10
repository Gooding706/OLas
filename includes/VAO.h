#pragma once
#include <glad.h>
#include<stdlib.h>
class VAO
{
    public:
        VAO(size_t buffers= 1);
        unsigned int GetID();
    private:
    unsigned int ID = 0;
};