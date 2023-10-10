#pragma once
#include <Mesh.h>
#include <vector>
#include <Camera.h>

class Renderer
{
    public:
        static Renderer* GetRenderer();
        static void AddObject(Mesh& Obj);
        static void SetCamera(Camera& Cam);
        static void RenderObjects();

        Renderer(const Renderer&) = delete;
    private:
        Renderer() {};
        void I_AddObject(Mesh* Obj);
        void I_RenderObjects();
        void I_SetCamera(Camera* Cam);
        void InitDefaultShader();
        static std::vector<Mesh*> RenderQueue;
        static Renderer* Instance;
        static unsigned int DefaultShader;
        void SetDefaultUniforms(unsigned int Program, Mesh& Obj);
        static Camera* RenderCamera;
};

