#include "Components/sprite.h"

#include <glad/glad.h>

Sprite::Sprite(const char* pathToTexture)
{
    int width, height;
    texture = LoadTexture(pathToTexture, &width, &height);

    float halfWidthf = static_cast<float>(width) / 2.0f;
    float halfHeightf = static_cast<float>(height) / 2.0f;

    float vertices[] = {
        -halfWidthf, -halfHeightf, 0.0f, 0.0f, 1.0f,
         halfWidthf, -halfHeightf, 0.0f, 1.0f, 1.0f,
        -halfWidthf,  halfHeightf, 0.0f, 0.0f, 0.0f,
         halfWidthf,  halfHeightf, 0.0f, 1.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 3, 2,
        0, 1, 3
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}