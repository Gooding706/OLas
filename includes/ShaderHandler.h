#pragma once
#include <glad.h>
#include <iostream>
#include <string>

namespace OShader
{
   struct ShaderBundle
   {
    unsigned int Frag, Vert;
   };

   void LogShader(GLenum Type, unsigned int ShaderObj);

   void LogProgram(GLenum Type, unsigned int ProgramObj);

   const ShaderBundle ParseShaders(const char* VertexPath, const char* FragmentPath);
   
   unsigned int CompileBundle(const ShaderBundle& Bundle);

   unsigned int CompileBundle(unsigned int Frag, unsigned int Vert);
}
