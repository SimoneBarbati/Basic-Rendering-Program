#include <GLFW/glfw3.h>

class Window
{
public:
    Window() = default;
    Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
    ~Window();

    void CreateGlfwWindow();
    GLFWwindow* GetGlfwWindow() const;
    const char* GetTitle() const;
    void SetTitle(const char* title);

    bool operator==(Window& other) { return this->GetGlfwWindow() == other.GetGlfwWindow(); }

private:
    int width = 640, height = 360;
    GLFWwindow* window = nullptr;
    GLFWwindow* sharedContext = nullptr;
    GLFWmonitor* windowMonitor = nullptr;
    const char* title = "myproject";
};

void FramebufferSizeCallback(GLFWwindow*, int width, int height);
