#include <Renderer.h>
#include <ShaderHandler.h>
#include <Mesh.h>
#include<iostream>
#include <GLFW/glfw3.h>

void Renderer::SetDefaultUniforms(unsigned int Program, Mesh& Obj)
{
    int UTime = glGetUniformLocation(Program, "UTime");
    int transform = glGetUniformLocation(Program, "transform");
    int projection = glGetUniformLocation(Program, "projection");
    int view = glGetUniformLocation(Program, "view");
    glUniform1f(UTime, glfwGetTime());
    glUniformMatrix4fv(transform, 1, GL_FALSE, glm::value_ptr(Obj.getTransformMatrix()));
    glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr((*RenderCamera).GetProjection()));
    glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr((*RenderCamera).GetView()));
}

void Renderer::InitDefaultShader()
{
    OShader::ShaderBundle bnd = OShader::ParseShaders("Shaders/Defvert.glsl", "Shaders/Deffrag.glsl");
    Renderer::DefaultShader = OShader::CompileBundle(bnd);
}

Renderer* Renderer::GetRenderer()
{
    if(Instance == nullptr)
    {
        Instance = new Renderer;
        Instance->InitDefaultShader();
    }
    return Instance;
}

void Renderer::AddObject(Mesh &Obj)
{
    (*GetRenderer()).I_AddObject(&Obj);
}

void Renderer::RenderObjects()
{
    (*GetRenderer()).I_RenderObjects();
}

void Renderer::SetCamera(Camera& Cam)
{
    (*GetRenderer()).I_SetCamera(&Cam);
}

void Renderer::I_SetCamera(Camera* Cam)
{
    this->RenderCamera = Cam;
}

void Renderer::I_AddObject(Mesh* Obj)
{
    RenderQueue.push_back(Obj);
}

void Renderer::I_RenderObjects()
{
    for(Mesh* V : Renderer::RenderQueue)
    {
        glUseProgram((*V).GetShaderID().value_or(Renderer::DefaultShader));
        if((*V).GetTexID().has_value())
        {
            glActiveTexture(GL_TEXTURE0 + (*V).GetTexID().value().second);
            glBindTexture(GL_TEXTURE_2D, (*V).GetTexID().value().first);
        }
        SetDefaultUniforms((*V).GetShaderID().value_or(Renderer::DefaultShader), (*V));
        glBindVertexArray((*V).getVAO().GetID());
        glDrawElements(GL_TRIANGLES, (*V).getEBO().GetCount(), GL_UNSIGNED_INT, 0);

        glUseProgram(0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

Renderer* Renderer::Instance = nullptr;
std::vector<Mesh*> Renderer::RenderQueue;
Camera* Renderer::RenderCamera;
unsigned int Renderer::DefaultShader;