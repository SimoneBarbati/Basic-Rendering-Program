#include <iostream>

#include <glad/glad.h>

#include "app.h"
#include "shapes.h"

Quad firstQuad = Quad(
    glm::vec3(440.0f, 260.0f, 0.0f),
    glm::vec3(840.0f, 260.0f, 0.0f),
    glm::vec3(440.0f, 460.0f, 0.0f),
    glm::vec3(840.0f, 460.0f, 0.0f)
);

Quad secondQuad = Quad(
    glm::vec3(-100.0f, -100.0f, 0.0f),
    glm::vec3(100.0f, -100.0f, 0.0f),
    glm::vec3(-100.0f, 100.0f, 0.0f),
    glm::vec3(100.0f, 100.0f, 0.0f)
);

App::App()
{
    if (Init())
        Run();
}

App::~App()
{
    glfwTerminate();
}

int App::Init()
{
    if (!glfwInit())
    {
#ifdef DEBUG
        std::cout << "Failed to Initialize GLFW" << std::endl;
#endif
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mainWindow = Window(1280, 720, "WINDOW");
    mainWindow.CreateGlfwWindow();
    glfwMakeContextCurrent(mainWindow.GetGlfwWindow());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
#ifdef DEBUG
        std::cout << "Failed to Initialiaze Glad" << std::endl;
#endif
        return 0;
    }

    renderer.Init();
    Shader shader = Shader("/home/simone/code/c++/myproject/assets/shaders/vertex.glsl", "/home/simone/code/c++/myproject/assets/shaders/fragment.glsl");
    shader.Compile();
    shaders.push_back(shader);

    mainCamera = Camera(glm::vec3(0.0f, 0.0f, 0.0f));

    return 1;
}

void App::HandleInput()
{
    GLFWwindow* window = mainWindow.GetGlfwWindow();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        mainCamera.position.y -= 10;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        mainCamera.position.x -= 10;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        mainCamera.position.y += 10;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        mainCamera.position.x += 10;
}

void App::Run()
{
    glfwMakeContextCurrent(mainWindow.GetGlfwWindow());
    shaders[0].UseShader();

    glDisable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    
    Render();
}

void App::Render()
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = mainCamera.GetProjectionMatrix();
    glm::mat4 view = glm::translate(glm::mat4(1.0f), -mainCamera.GetPosition());
    
    while (!glfwWindowShouldClose(mainWindow.GetGlfwWindow()))
    {
        HandleInput();
        glClear(GL_COLOR_BUFFER_BIT);
        
        shaders[0].UseShader();

        view = glm::translate(glm::mat4(1.0f), -mainCamera.GetPosition());
        shaders[0].SetMat4(model, "model");
        shaders[0].SetMat4(view, "view");
        shaders[0].SetMat4(projection, "projection");


        glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0.0f));
        float time = glfwGetTime() * 360.0f;
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(time), glm::vec3(0.0f, 1.0f, 1.0f));
        model = translation * rotation * glm::mat4(1.0f);
        shaders[0].SetMat4(model, "model");

        glm::vec3 color = glm::vec3(1.0f, 0.0f, 1.0f);
        shaders[0].SetVec3(color, "color");

        renderer.RenderQuad(secondQuad);

        glfwSwapBuffers(mainWindow.GetGlfwWindow());
        glfwPollEvents();

        while (auto error = glGetError()) { std::cout << error << std::endl; }
    }
}