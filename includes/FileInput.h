#pragma once
#include <stb_image.h>
#include <glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <Mesh.h>

namespace OPut
{
   Mesh loadModel(const char* path);
   std::string ReadFile(const char *Path);
   unsigned int genTexture(const char *Path);
}
