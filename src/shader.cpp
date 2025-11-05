#include <iostream>

#include <glad/glad.h>

#include "shader.h"

Shader::Shader(const char *pathToVertexShader, const char *pathToFragmentShader)
    : vertexShaderPath(pathToVertexShader), fragmentShaderPath(pathToFragmentShader)
{
}

int Shader::Compile()
{
    std::string vertexCode = ReadFromFile(vertexShaderPath);
    std::string fragmentCode = ReadFromFile(fragmentShaderPath);

    if (vertexCode.length() == 0 || fragmentCode.length() == 0)
        return 1;

    const char* c_vertexCode = vertexCode.c_str();
    const char* c_fragmentCode = fragmentCode.c_str();

    unsigned int vertexShader, fragmentShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &c_vertexCode, NULL);
    glCompileShader(vertexShader);
    {
        int success;
        char infoLog[1024];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } 
        
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &c_fragmentCode, NULL);
    glCompileShader(fragmentShader);
    {
        int success;
        char infoLog[1024];
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragmentShader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    {
        int success;
        char infoLog[1024];
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR: " << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

#ifdef DEBUG
    std::cout << "Shader Compiled" << std::endl;
#endif
    return 0;
}

unsigned int Shader::GetID()
{
    return ID;
}

void Shader::SetVertexShaderPath(const char *path)
{
    vertexShaderPath = path;
}

void Shader::SetFragmentShaderPath(const char *path)
{
    fragmentShaderPath = path;
}

void Shader::SetVec3(glm::vec3& vector, const char* vectorName)
{
    int location = getUniformLocation(vectorName);
    glUniform3fv(location, 1, glm::value_ptr(vector));
}

void Shader::SetMat4(glm::mat4& matrix, const char* matrixName)
{
    int location = getUniformLocation(matrixName);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::UseShader()
{
    glUseProgram(ID);
}

int Shader::getUniformLocation(const char* uniformName)
{
    return glGetUniformLocation(ID, uniformName);
}