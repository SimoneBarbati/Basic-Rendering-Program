#include <vector>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "window.h"
#include "shader.h"
#include "camera.h"
#include "renderer.h"

class App
{
public:
    App();
    ~App();
    int Init();
    void HandleInput();
    void Run();
    void Render();

private:
    std::vector<Shader> shaders;
    Camera mainCamera;
    Window mainWindow;
    Renderer renderer;

    unsigned int vao, vbo;
    double lastFrame = 0.0;
};