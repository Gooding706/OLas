#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <Types.h>

class Camera
{
    public:
    const glm::vec3& GetPosition();
    const glm::vec3& GetTarget();
    const glm::vec3& GetDirection();
    const glm::vec3& GetRight();
    const glm::vec3& GetUp();
    const glm::mat4& GetView();
    const glm::mat4& GetProjection();

    float GetFov();
    float GetAspectRatio();
    float GetNear();
    float GetFar();

    void SetPosition(const OTypes::Vec3& Position);
    void SetTarget(const OTypes::Vec3& Target);
    void SetDirection(const OTypes::Vec3& Direction);
    void SetRight(const OTypes::Vec3& Right);
    void SetUp(const OTypes::Vec3& Up);

    void SetFov(float Fov);
    void SetAspectRatio(float AspectRatio);
    void SetNear(float Near);
    void SetFar(float Far);

    private:
    void LinkView();
    void LinkProjection();

    float FOV = 45;

    //square by default
    float AspectRatio = 1;
    float Near = 0.01f;
    float Far = 100.0f;

    glm::vec3 CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 Target = glm::vec3(0.0f, 0.0f, 0.0f);
    //beware the direction is inverted as to what you would excpect b/c opengl is hell
    glm::vec3 Direction = glm::normalize(CameraPosition - Target);
    glm::vec3 Right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), Direction));
    glm::vec3 Up = glm::cross(Direction, Right);

    glm::mat4 CameraView = glm::lookAt(CameraPosition, Direction, Up);
    glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(FOV), AspectRatio, Near, Far);
};