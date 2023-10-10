#pragma once
#include <VBO.h>
#include <VAO.h>
#include <EBO.h>
#include <optional>
#include <Types.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


class Mesh
{
    public:
        //TODO: figure out how public I want this all to be

        Mesh(OTypes::Vertex* Shape, size_t VertexElements, unsigned int* Indices, size_t IndiceElements);
        
        //attach Shader or object will hold default shader;
        void AttachShader(unsigned int ShaderProgram);

        void AttachTexture(unsigned int Texture, int Slot = 0);

        VBO& getVBO();
        EBO& getEBO();
        VAO& getVAO();

        std::optional<unsigned int> GetShaderID();
        std::optional<std::pair<unsigned int, int>> GetTexID();

        void SetPosition(OTypes::Vec3 Position);
        void SetRotation(float Degrees, OTypes::Vec3 Orgin);
        void SetScale(OTypes::Vec3 Scale);
        glm::mat4& getTransformMatrix();
        const OTypes::Transform& ObjectTransforms();
        
    private:
        glm::vec3 Position;
        EBO MeshElementBuffer;
        VBO MeshVertexBuffer;
        VAO MeshArrayBuffer;
        std::optional<unsigned int> ShaderID;
        std::optional<std::pair<unsigned int, int>> TextureIDObj;
        glm::mat4 TransformationMatrix = glm::mat4(1);
        OTypes::Transform TransformValues = {{0,0,0}, {0,0,0}, {0,0,0}};
};