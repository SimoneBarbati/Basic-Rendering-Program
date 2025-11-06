#include <iostream>

#include "window.h"

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
    : width(width), height(height), title(title), windowMonitor(monitor), sharedContext(share)
{
}

Window::~Window()
{
    if (window != nullptr)
        glfwDestroyWindow(window);
}

void Window::CreateGlfwWindow()
{
    window = glfwCreateWindow(width, height, title, windowMonitor, sharedContext);
    if (window == NULL)
    {
#ifdef DEBUG
        std::cout << "Failed to create window" << std::endl;
#endif
        glfwTerminate();
        return;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
}

GLFWwindow* Window::GetGlfwWindow() const
{
    return window;
}

const char* Window::GetTitle() const
{
    return title;
}

void Window::SetTitle(const char* title)
{
    this->title = title;
}



void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}