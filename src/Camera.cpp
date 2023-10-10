#include <Camera.h>


const glm::vec3& Camera::GetPosition()
{
    return CameraPosition;
}

const glm::vec3& Camera::GetTarget()
{
    return Target;
}

const glm::vec3& Camera::GetDirection()
{
return Direction;
}

const glm::vec3& Camera::GetRight()
{
return Right;
}

const glm::vec3& Camera::GetUp()
{
return Up;
}

const glm::mat4& Camera::GetView()
{
return CameraView;
}

const glm::mat4& Camera::GetProjection()
{
return ProjectionMatrix;
}


float Camera::GetFov()
{
return FOV;
}

float Camera::GetAspectRatio()
{
return AspectRatio;
}

float Camera::GetNear()
{
return Near;
}

float Camera::GetFar()
{
return Far;
}


void Camera::SetPosition(const OTypes::Vec3 &Position)
{
this->CameraPosition = glm::vec3(Position.x, Position.y, Position.z);
LinkView();
}

void Camera::SetTarget(const OTypes::Vec3 &Target)
{
this->Target = glm::vec3(Target.x, Target.y, Target.z);
LinkView();
}

void Camera::SetDirection(const OTypes::Vec3 &Direction)
{
this->Direction = glm::vec3(Direction.x, Direction.y, Direction.z);
LinkView();
}

void Camera::SetRight(const OTypes::Vec3 &Right)
{
this->Right = glm::vec3(Right.x, Right.y, Right.z);
LinkView();
}

void Camera::SetUp(const OTypes::Vec3 &Up)
{
this->Up = glm::vec3(Up.x, Up.y, Up.z);
LinkView();
}


void Camera::SetFov(float Fov)
{
this->FOV = Fov;
LinkProjection();
}

void Camera::SetAspectRatio(float AspectRatio)
{
this->AspectRatio = AspectRatio;
LinkProjection();
}

void Camera::SetNear(float Near)
{
this->Near = Near;
LinkProjection();
}

void Camera::SetFar(float Far)
{
    this->Far = Far;
    LinkProjection();
}


void Camera::LinkView()
{
    Direction = glm::normalize(CameraPosition - Target);
    Right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), Direction));
    Up = glm::cross(Direction, Right);
    CameraView = glm::lookAt(CameraPosition, Direction, Up);
}

void Camera::LinkProjection()
{
    ProjectionMatrix = glm::perspective(glm::radians(FOV), AspectRatio, Near, Far);
}
