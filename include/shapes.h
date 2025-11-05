#pragma once

#include <glm/glm.hpp>

struct Quad
{
    Quad() = default;
    Quad(glm::vec3 topleft, glm::vec3 topright, glm::vec3 bottomleft, glm::vec3 bottomright)
    {
        this->topleft = topleft;
        this->topright = topright;
        this->bottomleft = bottomleft;
        this->bottomright = bottomright;
    }
    bool operator==(Quad other)
    {
        return 
            topleft == other.topleft &&
            topright == other.topright &&
            bottomleft == other.bottomleft &&
            bottomright == other.bottomright;
    }

    bool operator!=(Quad other)
    {
        return
            topleft != other.topleft ||
            topright != other.topright ||
            bottomleft != other.bottomleft ||
            bottomright != other.bottomright;
    }
    glm::vec3 topleft = glm::vec3(1.0f);
    glm::vec3 topright = glm::vec3(1.0f);
    glm::vec3 bottomleft = glm::vec3(1.0f);
    glm::vec3 bottomright = glm::vec3(1.0f);
};