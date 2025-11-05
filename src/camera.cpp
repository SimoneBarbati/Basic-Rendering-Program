#include "camera.h"

Camera::Camera(glm::vec3 pos)
    : position(pos)
{
    projectionMatrix = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -100.0f, 100.0f);
}

void Camera::Update()
{
}

glm::vec3 Camera::GetPosition()
{
    return position;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return projectionMatrix;
}