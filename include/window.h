#include <GLFW/glfw3.h>

#define WINDOW_MANAGER_MANAGED_TO_CHANGE_CONTEXT 0
#define WINDOW_MANAGER_FAILED_TO_CHANGE_CONTEXT 1

class Window
{
public:
    Window() = default;
    Window(int width, int height, const char* title);
    ~Window();

    void CreateGlfwWindow();
    GLFWwindow* GetGlfwWindow() const;
    const char* GetTitle() const;
    void SetTitle(const char* title);

    bool operator==(Window& other) { return this->GetGlfwWindow() == other.GetGlfwWindow(); }

private:
    int width = 640, height = 360;
    GLFWwindow* window = nullptr;
    const char* title = "myproject";
};

void FramebufferSizeCallback(GLFWwindow*, int width, int height);
