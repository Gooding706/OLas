#pragma once
#include <glad.h>
#include<stdlib.h>
#include <iostream>
class EBO
{
    public:
        unsigned int GetID();
        size_t GetCount();
        EBO(size_t buffers= 1);
        void AssignData(unsigned int* Indices, size_t Elements);

    private:
     unsigned int ID = 0;
     size_t IndicesCount;
};