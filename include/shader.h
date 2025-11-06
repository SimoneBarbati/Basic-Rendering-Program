#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "file_reader.h"

#define SINGLE_SHADER 1
#define SHADER_PROGRAM 2

class Shader
{
public:
    Shader(const char* pathToVertexShader, const char* pathToFragmentShader);
    unsigned int GetId();
    void UseShader();
    void SetVec3(glm::vec3& vector, const char* vectorName);
    void SetMat4(glm::mat4& matrix, const char* matrixName);

private:
    int getUniformLocation(const char* uniformName);
    bool compile(const char* pathToVertexShader, const char* pathToFragmentShader);
    bool areThereCompilationErrors(int type, unsigned int program);

    unsigned int id;
};
