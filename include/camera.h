#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    Camera() = default;
    Camera(glm::vec3 pos);

    void Update();
    glm::vec3 GetPosition();
    glm::mat4 GetProjectionMatrix();
    glm::vec3 position;
    glm::mat4 projectionMatrix;
};