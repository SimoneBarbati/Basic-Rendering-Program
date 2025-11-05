#pragma once

#include <iostream>

#ifdef DEBUG

#define LOG_ERROR(message) std::cout << "ERROR: " << message << std::endl;
#define LOG_MESSAGE(message) std::cout << "Program: " << message << std::endl;

#else

#define LOG_ERROR(message)
#define LOG_MESSAGE(message)

#endif
