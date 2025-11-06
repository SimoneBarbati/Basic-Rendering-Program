#include "camera.h"

Camera::Camera(glm::vec2 res, glm::vec3 pos)
    : resolution(res), position(pos)
{
    Update();
}

void Camera::Update()
{
    projectionMatrix = glm::ortho(0.0f, resolution.x, resolution.y, 0.0f, -100.0f, 100.0f);
}
