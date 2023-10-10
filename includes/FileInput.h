#pragma once
#include <stb_image.h>
#include <glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace OPut
{
   void loadModel(const char* path);
   std::string ReadFile(const char *Path);
   unsigned int genTexture(const char *Path);
}
