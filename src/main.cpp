#define GL_SILENCE_DEPRECATION

#include <iostream>
#include<glad.h>
#include <GLFW/glfw3.h>
 
#include <ShaderHandler.h>
#include <VBO.h>
#include<VAO.h>
#include<EBO.h>
#include<FileInput.h>
#include<Types.h>
#include<Mesh.h>

#include<Renderer.h>
#include<Camera.h>
#include<assimp/Importer.hpp>

 

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

int main(int argc, char** argv)
{

  //is it worth abstracting a windowing class if glfw already has most of that functionality native?
  glfwInit();

  #ifdef __APPLE__
  /* We need to explicitly ask for a 3.3 context on OS X */
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

  GLFWwindow* Window;
  if(!(Window = glfwCreateWindow(500, 500, "title", NULL, NULL)))
  {
     std::cout << "Failed to create window\n";
     return -1;
  }

  glfwMakeContextCurrent(Window);
  glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);

  if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
  {
    std::cout << "Failed to LoadGlad window\n";
    return -1;
  }


  OTypes::Vertex triangle[] =
  {
    {{0.5f,  0.5f, 0.0f}, {1.0f,  1.0f}},
    {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f,  0.5f, 0.0f}, {0.0f,  1.0f}}
  };

  unsigned int indices[] = 
  {
      0, 1, 3,
      1, 2, 3 
  };

  Mesh m1(triangle, 4, indices, 6);
  Camera Cam = Camera();

  OShader::ShaderBundle bnd = OShader::ParseShaders("Shaders/Defvert.glsl", "Shaders/frag.glsl");
  unsigned int Program = OShader::CompileBundle(bnd);


  m1.AttachShader(Program);


  //Should we hold uniforms that are obj specific, if so how? templates?
  int UTime = glGetUniformLocation(Program, "UTime");
  unsigned int TEX = OPut::genTexture("Shaders/Sex.jpg");

  m1.AttachTexture(TEX);


  Renderer::AddObject(m1);

  Renderer::SetCamera(Cam);
  
  
  double x, y = 0;
  m1.SetScale({2.0, 1, 1});
  
  OPut::loadModel("Models/monkey.glb");
  while(!glfwWindowShouldClose(Window))
  {
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    Renderer::RenderObjects();
    m1.SetRotation(((m1.ObjectTransforms().Rotation.y > 360) ? 0 : m1.ObjectTransforms().Rotation.y) + 0.001f, OTypes::Vec3{0.0f, 1.0f, 0.0f});
    glfwGetCursorPos(Window, &x, &y);
    glfwSwapBuffers(Window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}