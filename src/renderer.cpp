#include <glad/glad.h>

#include "renderer.h"
#include <iostream>

void Renderer::Init()
{
    glGenVertexArrays(1, &quadVao);
    glGenBuffers(1, &quadVbo);
    glGenBuffers(1, &quadEbo);

    glBindVertexArray(quadVao);

    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);
}

void Renderer::RenderQuad(Quad& quad)
{
    LoadQuadVertices(quad);
    glBindVertexArray(quadVao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::LoadQuadVertices(Quad& quad)
{   
    quadVertices = {
        quad.topleft.x, quad.topleft.y, quad.topleft.z,
        quad.topright.x, quad.topright.y, quad.topright.z,
        quad.bottomleft.x, quad.bottomleft.y, quad.bottomleft.z,
        quad.bottomright.x, quad.bottomright.y, quad.bottomright.z
    };

    glBindVertexArray(quadVao);
    glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
    glBufferData(GL_ARRAY_BUFFER, quadVertices.size() * sizeof(float), quadVertices.data(), GL_STATIC_DRAW);
}