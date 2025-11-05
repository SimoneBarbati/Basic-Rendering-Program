#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "file_reader.h"

class Shader
{
public:
    Shader(const char* pathToVertexShader, const char* pathToFragmentShader);
    int Compile();
    unsigned int GetID();
    void SetVertexShaderPath(const char* path);
    void SetFragmentShaderPath(const char* path);

    void SetVec3(glm::vec3& vector, const char* vectorName);
    void SetMat4(glm::mat4& matrix, const char* matrixName);

    void UseShader();

private:
    int getUniformLocation(const char* uniformName);

    unsigned int ID;
    const char* vertexShaderPath;
    const char* fragmentShaderPath;
};
