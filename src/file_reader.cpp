#include <iostream>

#include "file_reader.h"

std::string ReadFromFile(const char* path)
{
    std::ifstream file;
    std::stringstream fileStream;
    std::string result;

    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        file.open(path);
        fileStream << file.rdbuf();
        result = fileStream.str();
        file.close();
    }
    catch(const std::ifstream::failure& e)
    {
        std::cout << e.what() << '\n';
        return std::string("");
    }

    return result;
}