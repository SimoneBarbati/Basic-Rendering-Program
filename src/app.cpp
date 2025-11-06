#include <iostream>

#include <glad/glad.h>

#include "app.h"
#include "shapes.h"
#include "logger.h"

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

Sprite sprite;

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
        LOG_ERROR("FAILED TO INITIALIZE GLFW")
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    mainWindow = Window(mode->width, mode->height, "WINDOW", monitor, NULL);
    mainWindow.CreateGlfwWindow();
    glfwMakeContextCurrent(mainWindow.GetGlfwWindow());

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("FAILE TO INITIALIZE GLAD")
        return 0;
    }

    renderer.Init();
    Shader shader = Shader("../assets/shaders/vertex.glsl", "../assets/shaders/fragment.glsl");
    shaders.push_back(shader);

    Shader spriteShader = Shader("../assets/shaders/sprite_vertex.glsl", "../assets/shaders/sprite_fragment.glsl");
    shaders.push_back(spriteShader);

    mainCamera = Camera(glm::vec2(mode->width, mode->height), glm::vec3(0.0f, 0.0f, 0.0f));

    return 1;
}

void App::HandleInput(double deltaTime)
{
    double speed = 1000.0;
    GLFWwindow* window = mainWindow.GetGlfwWindow();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    mainCamera.position.y -= speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    mainCamera.position.x -= speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    mainCamera.position.y += speed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    mainCamera.position.x += speed * deltaTime;
}

void App::Run()
{
    glfwMakeContextCurrent(mainWindow.GetGlfwWindow());
    shaders[0].UseShader();

    glDisable(GL_DEPTH_TEST);
    glClearColor(1.0f / 255.0f, 1.0f / 255.0f, 1.0f / 255.0f, 1.0f);
    
    sprite = Sprite("../assets/images/texture.png");
    sprite.translation = glm::translate(glm::mat4(1.0f), glm::vec3(960.0f, 540.0f, 0.0));
    sprite.scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f));

    Render();
}

void App::Render()
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = mainCamera.GetProjectionMatrix();
    glm::mat4 view = glm::translate(glm::mat4(1.0f), -mainCamera.position);
    
    while (!glfwWindowShouldClose(mainWindow.GetGlfwWindow()))
    {
        double now = glfwGetTime();
        double deltaTime = now - lastFrame;
        lastFrame = now;

        HandleInput(deltaTime);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shaders[0].UseShader();

        view = glm::translate(glm::mat4(1.0f), -mainCamera.position);
        shaders[0].SetMat4(model, "model");
        shaders[0].SetMat4(view, "view");
        shaders[0].SetMat4(projection, "projection");
        
        renderer.RenderQuad(secondQuad, shaders[0], glm::vec3(0.0f, 0.0f, 1.0f));
        
        shaders[1].UseShader();
        shaders[1].SetMat4(view, "view");
        shaders[1].SetMat4(projection, "projection");

        renderer.RenderSprite(sprite, shaders[1]);

        glfwSwapBuffers(mainWindow.GetGlfwWindow());
        glfwPollEvents();

        while (auto error = glGetError()) { std::cout << error << std::endl; }
    }
}