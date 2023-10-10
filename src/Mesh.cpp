#include<Mesh.h>

Mesh::Mesh(OTypes::Vertex *Shape, size_t VertexElements, unsigned int *Indices, size_t IndiceElements) : MeshElementBuffer(1), MeshVertexBuffer(1), MeshArrayBuffer(1)
{
    MeshVertexBuffer.AssignData(Shape, VertexElements);
    MeshElementBuffer.AssignData(Indices, IndiceElements);
}
// attach Shader or object will hold default shader;
void Mesh::AttachShader(unsigned int ShaderProgram)
{
    ShaderID.emplace(ShaderProgram);
}

void Mesh::AttachTexture(unsigned int Texture, int Slot)
{
    TextureIDObj.emplace(std::pair<unsigned int, int>(Texture, Slot));
}

VBO& Mesh::getVBO(){
    return MeshVertexBuffer;
}
EBO& Mesh::getEBO(){
    return MeshElementBuffer;
}
VAO& Mesh::getVAO(){
    return MeshArrayBuffer;
}

std::optional<unsigned int> Mesh::GetShaderID(){
    return ShaderID;
}

std::optional<std::pair<unsigned int, int>> Mesh::GetTexID(){
    return TextureIDObj;
}


void Mesh::SetPosition(OTypes::Vec3 Position)
{
    TransformationMatrix = glm::translate(TransformationMatrix, glm::vec3(Position.x, Position.y, Position.z));
}

void Mesh::SetRotation(float Degrees, OTypes::Vec3 Orgin)
{
    TransformationMatrix = glm::rotate(TransformationMatrix, glm::radians(Degrees), glm::vec3(Orgin.x, Orgin.y, Orgin.z));
    TransformValues.Rotation = Orgin * Degrees;
}

void Mesh::SetScale(OTypes::Vec3 Scale)
{
    TransformationMatrix = glm::scale(TransformationMatrix, glm::vec3(Scale.x, Scale.y, Scale.z));
    TransformValues.Scale = Scale;
}

glm::mat4& Mesh::getTransformMatrix()
{
    return TransformationMatrix;
}

const OTypes::Transform& Mesh::ObjectTransforms()
{
    return TransformValues;
}