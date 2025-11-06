#pragma once

#include <glm/glm.hpp>

#include "texture_loader.h"

struct Sprite
{
    Sprite() = default;
    Sprite(const char* pathToTexture);

    unsigned int vao, vbo, ebo;
    unsigned int texture;
    glm::mat4 translation = glm::mat4(1.0f);
    glm::mat4 rotation = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
};