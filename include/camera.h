#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera() = default;
    Camera(glm::vec2 res, glm::vec3 pos);

    void Update();

    glm::vec2 GetResolution() const { return resolution; }
    void SetResolution(glm::vec2 resolution) { this->resolution = resolution; }
    glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }

    glm::vec3 position;
    
private:
    glm::vec2 resolution;
    glm::mat4 projectionMatrix;
};