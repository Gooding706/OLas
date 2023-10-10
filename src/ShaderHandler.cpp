#include <ShaderHandler.h>
#include <FileInput.h>

namespace OShader
{
   void LogShader(GLenum Type, unsigned int ShaderObj)
   {
      int success;
      char info[512];

      glGetShaderiv(ShaderObj, Type, &success);
      if(!success)
      {
         glGetShaderInfoLog(ShaderObj, 512, NULL, info);
         std::cout << "Shader failed to compile, here's why:" << info << "\n";
      }
      else
      {
         std::cout << "Shader compiled with success\n";
      }
   }

   void LogProgram(GLenum Type, unsigned int ProgramObj)
   {
      int success;
      char info[512];

      glGetProgramiv(ProgramObj, Type, &success);
      if(!success)
      {
         glGetProgramInfoLog(ProgramObj, 512, NULL, info);
         std::cout << "Program failed to compile, here's why:" << info << "\n";
      }
      else
      {
         std::cout << "Program compiled with success\n";
      }
   }


   const ShaderBundle ParseShaders(const char* VertexPath, const char* FragmentPath)
   {
      ShaderBundle ReturnBundle;
      
      auto fstring = OPut::ReadFile(FragmentPath);
      auto vstring = OPut::ReadFile(VertexPath);

      const char* VSrc = vstring.c_str();
      const char* FSrc = fstring.c_str();


      unsigned int Vert = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(Vert, 1, &VSrc, NULL);
      glCompileShader(Vert);
      LogShader(GL_COMPILE_STATUS, Vert);

      unsigned int Frag = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(Frag, 1, &FSrc, NULL);
      glCompileShader(Frag);
      LogShader(GL_COMPILE_STATUS, Frag);

      ReturnBundle = {Frag, Vert};
      return ReturnBundle;
   }
   
   unsigned int CompileBundle(const ShaderBundle& Bundle)
   {
      unsigned int Program = glCreateProgram();
      glAttachShader(Program, Bundle.Frag);
      glAttachShader(Program, Bundle.Vert);
      glLinkProgram(Program);

      LogProgram(GL_LINK_STATUS, Program);

      glDeleteShader(Bundle.Frag);
      glDeleteShader(Bundle.Vert);

      return Program;
   }

   unsigned int CompileBundle(unsigned int Frag, unsigned int Vert)
   {
      unsigned int Program = glCreateProgram();
      glAttachShader(Program, Frag);
      glAttachShader(Program, Vert);
      glLinkProgram(Program);
      LogProgram(GL_LINK_STATUS, Program);

      glDeleteShader(Frag);
      glDeleteShader(Vert);

      return Program;
   }
}
