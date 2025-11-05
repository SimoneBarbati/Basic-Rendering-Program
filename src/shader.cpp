#include <glad/glad.h>

#include "logger.h"
#include "shader.h"

Shader::Shader(const char* pathToVertexShader, const char* pathToFragmentShader)
{
    if (!compile(pathToVertexShader, pathToFragmentShader))
        LOG_ERROR("SHADER DID NOT COMPILE")
    else
        LOG_MESSAGE("Shader compiled correctly")
}

unsigned int Shader::GetId()
{
    return id;
}

void Shader::UseShader()
{
    glUseProgram(id);
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



int Shader::getUniformLocation(const char* uniformName)
{
    return glGetUniformLocation(id, uniformName);
}

bool Shader::compile(const char* pathToVertexShader, const char* pathToFragmentShader)
{
    std::string vertexCode = ReadFromFile(pathToVertexShader);
    std::string fragmentCode = ReadFromFile(pathToFragmentShader);

    if (vertexCode.length() == 0 || fragmentCode.length() == 0)
        return false;

    const char* c_vertexCode = vertexCode.c_str();
    const char* c_fragmentCode = fragmentCode.c_str();

    unsigned int vertexShader, fragmentShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &c_vertexCode, NULL);
    glCompileShader(vertexShader);
    if (areThereCompilationErrors(SINGLE_SHADER, vertexShader))
        return false;        

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &c_fragmentCode, NULL);
    glCompileShader(fragmentShader);
    if (areThereCompilationErrors(SINGLE_SHADER, fragmentShader))
        return false;

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);
    if (areThereCompilationErrors(SHADER_PROGRAM, id))
        return false;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

bool Shader::areThereCompilationErrors(int type, unsigned int program)
{
    int success;
    char infoLog[1024];

    if (type == SINGLE_SHADER)
    {
        glGetShaderiv(program, GL_COMPILE_STATUS, &success);
        if (success)
            return false;

        glGetShaderInfoLog(program, 1024, NULL, infoLog);
        LOG_ERROR("ERROR::SHADER_COMPILATION_ERROR: " << "\n" << infoLog)
    }

    else
    {
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (success)
            return false;
        
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        LOG_ERROR("ERROR::SHADER_LINKING_ERROR: " << "\n" << infoLog)
    }

    return true;
}